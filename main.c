#include <Python.h>

static struct electron {
   bool covalent;
   bool ionic;
   bool valent;
   bool exists;
   int energy;
};
static struct valence_ {
   electron[] electrons;
};

static struct atom {
   valence_ valence;
   electron[] inner;
   atomic_number;
};

static electron gen_electron(int shell){
   return electron(false, false, false, shell);
};

static atom render(char atomic_number) {
   int count1;
   for(int i = 1; i <= int(atomic_number); i +=8) {
      count1 = int(atomic_number) - i;
   };
   electron[count1] electrons_;
   int[int(atomic_number)][] count2;
   for(int i = 0; i <= int(atomic_number); i++) {
      int[] count3 = 0;
      for(int j = 0; j <= i; j++) {
         count3[j] = i;
      };
      count2[i] = count3;
   };
   int[] shells;
   for(int i=0; i <= int(atomic_number); i++) {
      for(int j =0; j <= i; j++) {
         shells[i] += count2[atomic_number - j][j];
      };
   };
   int count4 = atomic_number;
   int count5 = 0;
   int difference = 0;
   while (count4 > 0) {
      if(count4 - shells[count5] <= 0) {
         difference = 0 - count4 - shells[count5];
      };
      count4 -= shells[count5];
      count5 += 1;
   };
   electron[int(atomic_number)] render_blury;
   for(int i = 0; i <= count5; i++) {
     for(int j = 0; j <= shells[count5]; j++) {
        render_blury[j] = gen_electron(i);
      };
   };
   electron[count1] render_valence;
   for(int i = 0; i <= count1; i++) {
      render_valence[i] = render_blury[render_blury.length - i]
   };
   electron[] render_final;
   for(int i = 0; i <= atomic_number - count1; i++) {
     render_final[i] = render_blury[i]
   };
   return atom(render_valence, render_final, atomic_number)
};

static float calc_specific_heat1(int a) {
  if (a == 1) {
    return 14.304
  }
  if (a == 2) {
    return 5.193
  }
  if (a == 3) {
    return 3.6
  }
  if (a == 4) {
    return 1.82
  }
  if (a == 5) {
    return 1.02
  }
  if (a == 6) {
    return 0.71
  }
  if (a == 7) {
    return 1.04
  }
}

static struct atomInSpace {
  atom atom_;
  int[] position;
}
static atomInSpace fit_atom(atom, position) {
  return atomInSpace(atom, position)
}
static PyObject *method_fputs(PyObject *self, PyObject *args) {
  int[] *atoms = NULL;
  int[][] *positions = NULL;
  int *temp
  if(!PyArg_ParseTuple(args, "ss", &temp, &atoms, &positions)) {
       return NULL;
   }
  if(*atoms.length != *positions.length) {
    return NULL;
  }
  atomInSpace[] out;
  for(i=0; i<=atoms.length; i++) {
    out[i] = fit_atom(render(atoms[i]), positions[i]);
  };
  return PyObject(out);
};

static PyMethodDef FputsMethods[] = {
    {"MakeAtoms", method_fputs, METH_VARARGS, "Python atom simulator written in C"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef fputsmodule = {
    PyModuleDef_HEAD_INIT,
    "MakeAtoms",
    "Python atom simulator written in C",
    -1,
    FputsMethods
};

PyMODINIT_FUNC PyInit_fputs(void) {
    return PyModule_Create(&fputsmodule);
}
