// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "segment/Attrs.h"
#include "storage/FSHandler.h"

namespace milvus {
namespace codec {

class SSAttrsFormat {
 public:
    SSAttrsFormat() = default;

    void
    read(const storage::FSHandlerPtr& fs_ptr, segment::AttrsPtr& attrs_read);

    void
    write(const storage::FSHandlerPtr& fs_ptr, const segment::AttrsPtr& attr);

    void
    read_attrs(const storage::FSHandlerPtr& fs_ptr, const std::string& field_name, off_t offset, size_t num_bytes,
               std::vector<uint8_t>& raw_attrs);

    void
    read_uids(const storage::FSHandlerPtr& fs_ptr, std::vector<int64_t>& uids);

    // No copy and move
    SSAttrsFormat(const SSAttrsFormat&) = delete;
    SSAttrsFormat(SSAttrsFormat&&) = delete;

    SSAttrsFormat&
    operator=(const SSAttrsFormat&) = delete;
    SSAttrsFormat&
    operator=(SSAttrsFormat&&) = delete;

 private:
    void
    read_attrs_internal(const storage::FSHandlerPtr& fs_ptr, const std::string&, off_t, size_t, std::vector<uint8_t>&,
                        size_t&);

    void
    read_uids_internal(const storage::FSHandlerPtr& fs_ptr, const std::string&, std::vector<int64_t>&);

 private:
    const std::string raw_attr_extension_ = ".ra";
    const std::string user_id_extension_ = ".uid";
};

using SSAttrsFormatPtr = std::shared_ptr<SSAttrsFormat>;

}  // namespace codec
}  // namespace milvus
