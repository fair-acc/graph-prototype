#include <boost/ut.hpp>

#include <gnuradio-4.0/Block.hpp>
#include <gnuradio-4.0/Graph.hpp>

#include <fmt/format.h>

#if defined(__clang__) && __clang_major__ >= 15
// clang 16 does not like ut's default reporter_junit due to some issues with stream buffers and output redirection
template<>
auto boost::ut::cfg<boost::ut::override> = boost::ut::runner<boost::ut::reporter<>>{};
#endif

#include <iostream>
#include <numpy/arrayobject.h>
#include <Python.h>
#include <span>
#include <stdexcept>
#include <vector>

struct MyBlock;

template<typename T>
int
numpy_type() {
    return NPY_NOTYPE;
}

template<>
int
numpy_type<int>() {
    return NPY_INT;
}

template<>
int
numpy_type<double>() {
    return NPY_DOUBLE;
}

class PythonInterpreter {
public:
    template<typename TFunc>
    explicit PythonInterpreter(std::string_view pythonFunction, TFunc &&lambda, MyBlock *myBlockInstance = nullptr) {
        lambda();

        Py_Initialize();
        if (initialize_numpy() < 0) {
            throw std::runtime_error("Failed to initialize NumPy");
        }

        // Execute the Python script only once during initialization
        // Define Python function as a string
        PyRun_SimpleString(pythonFunction.data());

        PyObject *pCapsule = PyCapsule_New(static_cast<void *>(myBlockInstance), "MyBlock", nullptr);
        if (!pCapsule) {
            throw std::runtime_error("Failed to create a capsule for MyBlock");
        }

        PyObject *pMainModule = PyImport_AddModule("__main__");
        PyObject *pMainDict   = PyModule_GetDict(pMainModule);
        PyDict_SetItemString(pMainDict, "capsule", pCapsule);

        PyObject *pMyBlockClass = PyRun_String("import MyBlock\n"
                                               "class MyBlockWrapper:\n"
                                               "    def __init__(self, capsule):\n"
                                               "        self.capsule = capsule\n"
                                               "    def tagAvailable(self):\n"
                                               "        return MyBlock.tagAvailable(self.capsule)\n"
                                               "    def getTag(self):\n"
                                               "        return MyBlock.getTag(self.capsule)\n"
                                               "    def getSettings(self):\n"
                                               "        return MyBlock.getSettings(self.capsule)\n"
                                               "    def setSettings(self, settings):\n"
                                               "        MyBlock.setSettings(self.capsule, settings)\n"
                                               "\n"
                                               "this_block = MyBlockWrapper(capsule)\n",
                                               Py_file_input, pMainDict, pMainDict);

        // Retrieve the MyBlockWrapper class object
        PyObject *pMyBlockWrapperClass = PyDict_GetItemString(pMainDict, "MyBlockWrapper");
        if (!pMyBlockWrapperClass) {
            PyErr_Print();
            throw std::runtime_error("Failed to retrieve MyBlockWrapper class");
        }

        // Retrieve the this_block
        PyObject *pInstance = PyDict_GetItemString(pMainDict, "this_block");
        if (!pInstance) {
            PyErr_Print();
            throw std::runtime_error("Failed to retrieve this_block");
        }

        // Check if pInstance is an instance of MyBlockWrapper
        if (PyObject_IsInstance(pInstance, pMyBlockWrapperClass) != 1) {
            PyErr_Print();
            throw std::runtime_error("this_block is not an instance of MyBlockWrapper");
        }

        // Check for execution errors
        if (!pMyBlockClass) {
            PyErr_Print();
            throw std::runtime_error("Failed to create MyBlockWrapper");
        }
        Py_INCREF(pCapsule); // Increment if you're using pCapsule elsewhere
    }

    ~PythonInterpreter() { Py_Finalize(); }

    // Prevent copying and moving
    PythonInterpreter(const PythonInterpreter &) = delete;
    PythonInterpreter &
    operator=(const PythonInterpreter &)
            = delete;
    PythonInterpreter(PythonInterpreter &&) = delete;
    PythonInterpreter &
    operator=(PythonInterpreter &&)
            = delete;

    void
    callPythonFunction(const std::span<std::span<const int>> &ins, const std::span<std::span<int>> &outs) {
        PyObject *pModule = PyImport_AddModule("__main__");
        PyObject *pFunc   = PyObject_GetAttrString(pModule, "process_bulk");

        if (!pFunc || !PyCallable_Check(pFunc)) {
            PyErr_Print();
            throw std::runtime_error("Python function process_bulk not found or is not callable");
        }

        PyObject *pIns = PyList_New(static_cast<Py_ssize_t>(ins.size()));
        for (size_t i = 0; i < ins.size(); ++i) {
            PyObject *np_array = spanToNumpyArray(ins[i]);
            PyList_SetItem(pIns, i, np_array);
        }

        PyObject *pOuts = PyList_New(static_cast<Py_ssize_t>(outs.size()));
        for (size_t i = 0; i < outs.size(); ++i) {
            PyObject *np_array = spanToNumpyArray(outs[i]);
            PyList_SetItem(pOuts, i, np_array);
        }

        PyObject *pArgs = PyTuple_New(2);
        PyTuple_SetItem(pArgs, 0, pIns);
        PyTuple_SetItem(pArgs, 1, pOuts);

        PyObject *pValue = PyObject_CallObject(pFunc, pArgs);

        Py_DECREF(pArgs);
        Py_DECREF(pFunc);

        if (!pValue) {
            PyErr_Print();
            throw std::runtime_error("Python function call failed");
        }

        Py_DECREF(pValue);
    }

private:
    int
    initialize_numpy() {
        import_array1(-1);
        return 0;
    }

    template<typename T>
    PyObject *
    spanToNumpyArray(const std::span<const T> &span) {
        npy_intp  size     = span.size();
        PyObject *np_array = PyArray_SimpleNewFromData(1, &size, numpy_type<T>(), (void *) span.data());
        if (!np_array) throw std::runtime_error("Unable to create NumPy array");
        Py_INCREF(np_array);
        return np_array;
    }

    template<typename T>
    PyObject *
    spanToNumpyArray(const std::span<T> &span) {
        npy_intp  size     = span.size();
        PyObject *np_array = PyArray_SimpleNewFromData(1, &size, numpy_type<T>(), (void *) span.data());
        if (!np_array) throw std::runtime_error("Unable to create NumPy array");
        Py_INCREF(np_array);
        return np_array;
    }
};

using namespace gr;

struct MyBlock {
    using property_map = std::map<std::string, std::string, std::less<>>;
    using tag_type     = std::string;
    PythonInterpreter _interpreter;
    property_map      _settingsMap{ { "key1", "value1" }, { "key2", "value2" } };
    bool              _tagAvailable = false;
    tag_type          _tag          = "Simulated Tag";

    template<typename TFunc>
    explicit MyBlock(std::string_view pythonScript, TFunc &&lambda) : _interpreter(pythonScript, std::forward<TFunc>(lambda), this) {}

    const property_map &
    getSettings() const {
        return _settingsMap;
    }

    bool
    setSettings(const property_map &newSettings) {
        if (newSettings.empty()) {
            return false;
        }
        for (const auto &[key, value] : newSettings) {
            _settingsMap.insert_or_assign(key, value);
        }
        return true;
    }

    bool
    tagAvailable() {
        _tagAvailable = !_tagAvailable;
        return _tagAvailable;
    }

    tag_type
    getTag() {
        return _tag;
    }

    work::Status
    processBulk(const std::span<std::span<const int>> &ins, const std::span<std::span<int>> &outs) {
        _interpreter.callPythonFunction(ins, outs);

        return work::Status::OK;
    }
};

extern "C" {

static MyBlock *
getMyBlockFromCapsule(PyObject *capsule) {
    return static_cast<MyBlock *>(PyCapsule_GetPointer(capsule, "MyBlock"));
}

static PyObject *
MyBlock_TagAvailable(PyObject *self, PyObject *args) {
    PyObject *capsule;
    if (!PyArg_ParseTuple(args, "O", &capsule)) {
        return nullptr;
    }
    MyBlock *myBlock = getMyBlockFromCapsule(capsule);
    return myBlock->tagAvailable() ? Py_True : Py_False;
}

static PyObject *
MyBlock_GetTag(PyObject *self, PyObject *args) {
    PyObject *capsule;
    if (!PyArg_ParseTuple(args, "O", &capsule)) {
        return nullptr;
    }
    MyBlock *myBlock = getMyBlockFromCapsule(capsule);
    return PyUnicode_FromString(myBlock->getTag().c_str());
}

static PyObject *
MyBlock_GetSettings(PyObject *self, PyObject *args) {
    PyObject *capsule;
    if (!PyArg_ParseTuple(args, "O", &capsule)) {
        return nullptr;
    }
    MyBlock    *myBlock  = getMyBlockFromCapsule(capsule);
    const auto &settings = myBlock->getSettings();

    PyObject *dict = PyDict_New();
    for (const auto &[key, value] : settings) {
        PyDict_SetItemString(dict, key.c_str(), PyUnicode_FromString(value.c_str()));
    }
    return dict;
}

static PyObject *
MyBlock_SetSettings(PyObject *self, PyObject *args) {
    PyObject *capsule;
    PyObject *settingsDict;
    if (!PyArg_ParseTuple(args, "OO", &capsule, &settingsDict)) {
        return nullptr;
    }
    MyBlock *myBlock = getMyBlockFromCapsule(capsule);
    if (!PyDict_Check(settingsDict)) {
        PyErr_SetString(PyExc_TypeError, "Settings must be a dictionary");
        return nullptr;
    }

    MyBlock::property_map newSettings;
    PyObject             *key, *value;
    Py_ssize_t            pos = 0;
    while (PyDict_Next(settingsDict, &pos, &key, &value)) {
        const char *keyStr   = PyUnicode_AsUTF8(key);
        const char *valueStr = PyUnicode_AsUTF8(value);
        newSettings[keyStr]  = valueStr;
    }

    myBlock->setSettings(newSettings);
    Py_RETURN_NONE;
}

static PyMethodDef MyBlockMethods[] = { { "tagAvailable", MyBlock_TagAvailable, METH_VARARGS, "Check if a tag is available" },
                                        { "getTag", MyBlock_GetTag, METH_VARARGS, "Get the current tag" },
                                        { "getSettings", MyBlock_GetSettings, METH_VARARGS, "Get the settings" },
                                        { "setSettings", MyBlock_SetSettings, METH_VARARGS, "Set the settings" },
                                        { nullptr, nullptr, 0, nullptr } };

static struct PyModuleDef myBlockModule = { PyModuleDef_HEAD_INIT, "MyBlock", nullptr, -1, MyBlockMethods };

PyMODINIT_FUNC
PyInit_myBlock() {
    return PyModule_Create(&myBlockModule);
}
}

int
main() {
    try {
        // Your Python script
        std::string pythonScript =
                R"(
import time
counter = 0

def process_bulk(ins, outs):
    global counter
    start = time.time()
    print('Start Python processing iteration: {}'.format(counter))
    # Print current settings
    settings = this_block.getSettings()
    print("Current settings:", settings)

    # tag handling
    if this_block.tagAvailable():
        tag = this_block.getTag()
        print('Tag:', tag)

    counter += 1

    # process the input->output samples
    for i in range(len(ins)):
        outs[i][:] = ins[i] * 2

    # Update settings with the counter
    settings["counter"] = str(counter)
    this_block.setSettings(settings)

    print('Stop Python processing - time: {} seconds'.format(time.time() - start))
)";

        MyBlock                           myBlock(pythonScript, []() { PyImport_AppendInittab("MyBlock", &PyInit_myBlock); });
        int                               count = 0;
        std::vector<int>                  data1 = { 1, 2, 3 };
        std::vector<int>                  data2 = { 4, 5, 6 };
        std::vector<int>                  out1(3);
        std::vector<int>                  out2(3);
        std::vector<std::span<int>>       outs = { out1, out2 };
        std::vector<std::span<const int>> ins  = { data1, data2 };
        for (const auto &span : ins) {
            fmt::println("InPort[{}] : [{}]", count++, fmt::join(span, ", "));
        }
        fmt::println("");

        for (std::size_t i = 0; i < 3; i++) {
            fmt::println("C++ processing iteration: {}", i);
            std::vector<std::span<const int>> constOuts(outs.begin(), outs.end());

            myBlock.processBulk(i == 0 ? ins : constOuts, outs);

            fmt::println("C++ side got:");
            fmt::println("settings: {}", myBlock._settingsMap);
            for (const auto &span : outs) {
                fmt::println("OutPort[{}] : [{}]", count++, fmt::join(span, ", "));
            }
            fmt::println("");
        }

    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
