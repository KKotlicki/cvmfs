/**
 * This file is part of the CernVM File System.
 */

#include <stdint.h>

namespace compat {

struct InodeGenerationInfoV1 {
  unsigned version;
  uint64_t initial_revision;
  uint32_t incarnation;
  uint32_t overflow_counter;  // not used any more
  uint64_t inode_generation;
};

struct FuseStateV1 {
  unsigned version;
  bool cache_symlinks;
  bool has_dentry_expire;
};

} // namespace compat