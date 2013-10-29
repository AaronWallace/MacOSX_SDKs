
#ifdef _UMATHMODULE

#ifdef NPY_ENABLE_SEPARATE_COMPILATION
extern NPY_NO_EXPORT PyTypeObject PyUFunc_Type;
#else
NPY_NO_EXPORT PyTypeObject PyUFunc_Type;
#endif

#ifdef NPY_ENABLE_SEPARATE_COMPILATION
    extern NPY_NO_EXPORT PyTypeObject PyUFunc_Type;
#else
    NPY_NO_EXPORT PyTypeObject PyUFunc_Type;
#endif

NPY_NO_EXPORT PyObject * PyUFunc_FromFuncAndData \
       (PyUFuncGenericFunction *, void **, char *, int, int, int, int, char *, char *, int);
NPY_NO_EXPORT int PyUFunc_RegisterLoopForType \
       (PyUFuncObject *, int, PyUFuncGenericFunction, int *, void *);
NPY_NO_EXPORT int PyUFunc_GenericFunction \
       (PyUFuncObject *, PyObject *, PyObject *, PyArrayObject **);
NPY_NO_EXPORT void PyUFunc_f_f_As_d_d \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_d_d \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_f_f \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_g_g \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_F_F_As_D_D \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_F_F \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_D_D \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_G_G \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_O_O \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_ff_f_As_dd_d \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_ff_f \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_dd_d \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_gg_g \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_FF_F_As_DD_D \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_DD_D \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_FF_F \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_GG_G \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_OO_O \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_O_O_method \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_OO_O_method \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT void PyUFunc_On_Om \
       (char **, npy_intp *, npy_intp *, void *);
NPY_NO_EXPORT int PyUFunc_GetPyValues \
       (char *, int *, int *, PyObject **);
NPY_NO_EXPORT int PyUFunc_checkfperr \
       (int, PyObject *, int *);
NPY_NO_EXPORT void PyUFunc_clearfperr \
       (void);
NPY_NO_EXPORT int PyUFunc_getfperr \
       (void);
NPY_NO_EXPORT int PyUFunc_handlefperr \
       (int, PyObject *, int, int *);
NPY_NO_EXPORT int PyUFunc_ReplaceLoopBySignature \
       (PyUFuncObject *, PyUFuncGenericFunction, int *, PyUFuncGenericFunction *);
NPY_NO_EXPORT PyObject * PyUFunc_FromFuncAndDataAndSignature \
       (PyUFuncGenericFunction *, void **, char *, int, int, int, int, char *, char *, int, const char *);
NPY_NO_EXPORT int PyUFunc_SetUsesArraysAsData \
       (void **, size_t);

#else

#if defined(PY_UFUNC_UNIQUE_SYMBOL)
#define PyUFunc_API PY_UFUNC_UNIQUE_SYMBOL
#endif

#if defined(NO_IMPORT) || defined(NO_IMPORT_UFUNC)
extern void **PyUFunc_API;
#else
#if defined(PY_UFUNC_UNIQUE_SYMBOL)
void **PyUFunc_API;
#else
static void **PyUFunc_API=NULL;
#endif
#endif

#define PyUFunc_Type (*(PyTypeObject *)PyUFunc_API[0])
#define PyUFunc_FromFuncAndData \
        (*(PyObject * (*)(PyUFuncGenericFunction *, void **, char *, int, int, int, int, char *, char *, int)) \
         PyUFunc_API[1])
#define PyUFunc_RegisterLoopForType \
        (*(int (*)(PyUFuncObject *, int, PyUFuncGenericFunction, int *, void *)) \
         PyUFunc_API[2])
#define PyUFunc_GenericFunction \
        (*(int (*)(PyUFuncObject *, PyObject *, PyObject *, PyArrayObject **)) \
         PyUFunc_API[3])
#define PyUFunc_f_f_As_d_d \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[4])
#define PyUFunc_d_d \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[5])
#define PyUFunc_f_f \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[6])
#define PyUFunc_g_g \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[7])
#define PyUFunc_F_F_As_D_D \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[8])
#define PyUFunc_F_F \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[9])
#define PyUFunc_D_D \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[10])
#define PyUFunc_G_G \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[11])
#define PyUFunc_O_O \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[12])
#define PyUFunc_ff_f_As_dd_d \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[13])
#define PyUFunc_ff_f \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[14])
#define PyUFunc_dd_d \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[15])
#define PyUFunc_gg_g \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[16])
#define PyUFunc_FF_F_As_DD_D \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[17])
#define PyUFunc_DD_D \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[18])
#define PyUFunc_FF_F \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[19])
#define PyUFunc_GG_G \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[20])
#define PyUFunc_OO_O \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[21])
#define PyUFunc_O_O_method \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[22])
#define PyUFunc_OO_O_method \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[23])
#define PyUFunc_On_Om \
        (*(void (*)(char **, npy_intp *, npy_intp *, void *)) \
         PyUFunc_API[24])
#define PyUFunc_GetPyValues \
        (*(int (*)(char *, int *, int *, PyObject **)) \
         PyUFunc_API[25])
#define PyUFunc_checkfperr \
        (*(int (*)(int, PyObject *, int *)) \
         PyUFunc_API[26])
#define PyUFunc_clearfperr \
        (*(void (*)(void)) \
         PyUFunc_API[27])
#define PyUFunc_getfperr \
        (*(int (*)(void)) \
         PyUFunc_API[28])
#define PyUFunc_handlefperr \
        (*(int (*)(int, PyObject *, int, int *)) \
         PyUFunc_API[29])
#define PyUFunc_ReplaceLoopBySignature \
        (*(int (*)(PyUFuncObject *, PyUFuncGenericFunction, int *, PyUFuncGenericFunction *)) \
         PyUFunc_API[30])
#define PyUFunc_FromFuncAndDataAndSignature \
        (*(PyObject * (*)(PyUFuncGenericFunction *, void **, char *, int, int, int, int, char *, char *, int, const char *)) \
         PyUFunc_API[31])
#define PyUFunc_SetUsesArraysAsData \
        (*(int (*)(void **, size_t)) \
         PyUFunc_API[32])

static int
_import_umath(void)
{
  PyObject *numpy = PyImport_ImportModule("numpy.core.umath");
  PyObject *c_api = NULL;

  if (numpy == NULL) {
      PyErr_SetString(PyExc_ImportError, "numpy.core.umath failed to import");
      return -1;
  }
  c_api = PyObject_GetAttrString(numpy, "_UFUNC_API");
  Py_DECREF(numpy);
  if (c_api == NULL) {
      PyErr_SetString(PyExc_AttributeError, "_UFUNC_API not found");
      return -1;
  }

#if PY_VERSION_HEX >= 0x03000000
  if (!PyCapsule_CheckExact(c_api)) {
      PyErr_SetString(PyExc_RuntimeError, "_UFUNC_API is not PyCapsule object");
      Py_DECREF(c_api);
      return -1;
  }
  PyUFunc_API = (void **)PyCapsule_GetPointer(c_api, NULL);
#else
  if (!PyCObject_Check(c_api)) {
      PyErr_SetString(PyExc_RuntimeError, "_UFUNC_API is not PyCObject object");
      Py_DECREF(c_api);
      return -1;
  }
  PyUFunc_API = (void **)PyCObject_AsVoidPtr(c_api);
#endif
  Py_DECREF(c_api);
  if (PyUFunc_API == NULL) {
      PyErr_SetString(PyExc_RuntimeError, "_UFUNC_API is NULL pointer");
      return -1;
  }
  return 0;
}

#define import_umath() { UFUNC_NOFPE if (_import_umath() < 0) {PyErr_Print(); PyErr_SetString(PyExc_ImportError, "numpy.core.umath failed to import"); return; }}

#define import_umath1(ret) { UFUNC_NOFPE if (_import_umath() < 0) {PyErr_Print(); PyErr_SetString(PyExc_ImportError, "numpy.core.umath failed to import"); return ret; }}

#define import_umath2(msg, ret) { UFUNC_NOFPE if (_import_umath() < 0) {PyErr_Print(); PyErr_SetString(PyExc_ImportError, msg); return ret; }}

#define import_ufunc() { UFUNC_NOFPE if (_import_umath() < 0) {PyErr_Print(); PyErr_SetString(PyExc_ImportError, "numpy.core.umath failed to import"); }}


#endif
