/**
 * This file is part of the CernVM File System.
 *
 * Building blocks to serialize and deserialize states. Functions are exposed
 * as C functions because the bridge library is build with (possibly) different
 * C++ standard / ABI than the rest of cvmfs.
 */

#ifndef CVMFS_BRIDGE_MARSHAL_H_
#define CVMFS_BRIDGE_MARSHAL_H_

#include <cstddef>
#include <cstdint>

#include "util/export.h"

extern "C" {

CVMFS_EXPORT size_t cvm_bridge_write_uint32(const uint32_t *value,
                                            void *buffer);
CVMFS_EXPORT size_t cvm_bridge_read_uint32(const void *buffer, uint32_t *value);

CVMFS_EXPORT size_t cvm_bridge_write_uint64(const uint64_t *value,
                                            void *buffer);
CVMFS_EXPORT size_t cvm_bridge_read_uint64(const void *buffer, uint64_t *value);

CVMFS_EXPORT size_t cvm_bridge_write_uint(const unsigned *value, void *buffer);
CVMFS_EXPORT size_t cvm_bridge_read_uint(const void *buffer, unsigned *value);

CVMFS_EXPORT size_t cvm_bridge_write_bool(const bool *value, void *buffer);
CVMFS_EXPORT size_t cvm_bridge_read_bool(const void *buffer, bool *value);

}  // extern "C"

#endif  // CVMFS_BRIDGE_MARSHAL_H_