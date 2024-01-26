/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "cenc_pssh.h"

namespace dash {
namespace mpd {

CencPssh::CencPssh() :
    Descriptor("CencPssh") {
}

const std::string& CencPssh::GetPssh() const {
  return pssh_;
}

} // namespace mpd
} // namespace dash
