/* pocl_builtin_kernels.h - builtin kernel related function declarations

   Copyright (c) 2022-2024 PoCL developers

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to
   deal in the Software without restriction, including without limitation the
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
   sell copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
   IN THE SOFTWARE.
*/

#ifndef POCL_BUILTIN_KERNELS_H
#define POCL_BUILTIN_KERNELS_H

#include "pocl_cl.h"
#include "pocl_export.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define BIKERNELS POCL_CDBI_LAST
  POCL_EXPORT extern pocl_kernel_metadata_t pocl_BIDescriptors[BIKERNELS];

  POCL_EXPORT
  void pocl_init_builtin_kernel_metadata ();

  POCL_EXPORT
  int pocl_setup_builtin_metadata (cl_device_id device,
                                   cl_program program,
                                   unsigned program_device_i);

  POCL_EXPORT
  int pocl_sanitize_builtin_kernel_name (cl_kernel kernel,
                                         char **saved_name);

  POCL_EXPORT
  int pocl_restore_builtin_kernel_name (cl_kernel kernel,
                                        char *saved_name);

  typedef int
  pocl_validate_khr_gemm_callback_t (cl_bool TransA,
                                     cl_bool TransB,
                                     const cl_tensor_desc_exp *TenA,
                                     const cl_tensor_desc_exp *TenB,
                                     const cl_tensor_desc_exp *TenCIOpt,
                                     const cl_tensor_desc_exp *TenCOut,
                                     const cl_tensor_datatype_value_exp *Alpha,
                                     const cl_tensor_datatype_value_exp *Beta);

  /* GemmCB can be NULL, in which case the "generic" validation is run,
   * which checks the basic sanity. If it's non-NULL it's expected to check
   * device-specific validity. */
  POCL_EXPORT
  int pocl_validate_dbk_attributes (cl_dbk_id_exp kernel_id,
                                    const void *kernel_attributes,
                                    pocl_validate_khr_gemm_callback_t GemmCB);

  void *pocl_copy_defined_builtin_attributes (cl_dbk_id_exp kernel_id,
                                              const void *kernel_attributes);

  int pocl_release_defined_builtin_attributes (cl_dbk_id_exp kernel_id,
                                               void *kernel_attributes);

  POCL_EXPORT uint64_t
  pocl_serialize_cl_tensor_desc (const cl_tensor_desc_exp *t, char **buf);
  POCL_EXPORT uint64_t pocl_serialize_dbk_attribs (cl_dbk_id_exp id,
                                                   const void *attributes,
                                                   char **buf);

  POCL_EXPORT int pocl_deserialize_cl_tensor_desc (cl_tensor_desc_exp *t,
                                                   const char **buf);

  POCL_EXPORT int pocl_deserialize_dbk_attribs (cl_dbk_id_exp *id,
                                                void **attributes,
                                                const char **buf);
#ifdef __cplusplus
}
#endif

#endif
