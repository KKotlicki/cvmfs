/**
 * This file is part of the CernVM File System.
 */

#include <gtest/gtest.h>

#include "bridge/marshal.h"
#include "bridge/migrate.h"
#include "fuse_inode_gen.h"
#include "fuse_state.h"
#include "state.h"
#include "util/smalloc.h"

#include <cstdint>
#include <cstring>

TEST(T_State, OpenFilesCounter) {
  unsigned char buffer[4];
  EXPECT_EQ(4u, StateSerializer::SerializeOpenFilesCounter(42, NULL));
  EXPECT_EQ(4u, StateSerializer::SerializeOpenFilesCounter(42, buffer));
  uint32_t check;
  EXPECT_EQ(4u, StateSerializer::DeserializeOpenFilesCounter(buffer, &check));
  EXPECT_EQ(42u, check);

  uint32_t *value_v1 = new uint32_t(137);
  void *v2s = cvm_bridge_migrate_nfiles_ctr_v1v2s(value_v1);
  EXPECT_EQ(4u, StateSerializer::DeserializeOpenFilesCounter(v2s, &check));
  cvm_bridge_migrate_nfiles_ctr_v1v2s(value_v1);
  EXPECT_EQ(137u, check);
}

TEST(T_State, InodeGeneration) {
  cvmfs::InodeGenerationInfo value;
  value.initial_revision = 137;
  value.incarnation = 138;
  value.overflow_counter = 139;
  value.inode_generation = 140;

  size_t nbytes = StateSerializer::SerializeInodeGeneration(value, NULL);
  void *buffer = smalloc(nbytes);
  EXPECT_EQ(nbytes, StateSerializer::SerializeInodeGeneration(value, buffer));

  cvmfs::InodeGenerationInfo check;
  EXPECT_EQ(nbytes,
            StateSerializer::DeserializeInodeGeneration(buffer, &check));
  free(buffer);

  EXPECT_EQ(value.version, check.version);
  EXPECT_EQ(value.initial_revision, check.initial_revision);
  EXPECT_EQ(value.incarnation, check.incarnation);
  EXPECT_EQ(value.overflow_counter, check.overflow_counter);
  EXPECT_EQ(value.inode_generation, check.inode_generation);

  cvmfs::InodeGenerationInfo *value_v1 = new cvmfs::InodeGenerationInfo();
  memcpy(value_v1, &value, sizeof(value));
  void *v2s = cvm_bridge_migrate_inode_generation_v1v2s(value_v1);

  EXPECT_EQ(nbytes, StateSerializer::DeserializeInodeGeneration(v2s, &check));
  cvm_bridge_free_inode_generation_v1(value_v1);

  EXPECT_EQ(value.version, check.version);
  EXPECT_EQ(value.initial_revision, check.initial_revision);
  EXPECT_EQ(value.incarnation, check.incarnation);
  EXPECT_EQ(value.overflow_counter, check.overflow_counter);
  EXPECT_EQ(value.inode_generation, check.inode_generation);
}

TEST(T_State, FuseState) {
  cvmfs::FuseState value;
  value.cache_symlinks = true;
  value.has_dentry_expire = true;

  size_t nbytes = StateSerializer::SerializeFuseState(value, NULL);
  void *buffer = smalloc(nbytes);
  EXPECT_EQ(nbytes, StateSerializer::SerializeFuseState(value, buffer));

  cvmfs::FuseState check;
  EXPECT_EQ(nbytes, StateSerializer::DeserializeFuseState(buffer, &check));
  free(buffer);

  EXPECT_EQ(value.version, check.version);
  EXPECT_EQ(value.cache_symlinks, check.cache_symlinks);
  EXPECT_EQ(value.has_dentry_expire, check.has_dentry_expire);

  cvmfs::FuseState *value_v1 = new cvmfs::FuseState();
  memcpy(value_v1, &value, sizeof(value));
  void *v2s = cvm_bridge_migrate_fuse_state_v1v2s(value_v1);

  EXPECT_EQ(nbytes, StateSerializer::DeserializeFuseState(v2s, &check));
  cvm_bridge_free_fuse_state_v1(value_v1);

  EXPECT_EQ(value.version, check.version);
  EXPECT_EQ(value.cache_symlinks, check.cache_symlinks);
  EXPECT_EQ(value.has_dentry_expire, check.has_dentry_expire);
}