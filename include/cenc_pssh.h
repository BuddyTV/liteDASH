/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_CENCPSSH_H_
#define DASH_CENCPSSH_H_

#include "descriptor.h"

#include <string>

namespace dash {
namespace mpd {

class CencPssh: public Descriptor {
  public:
    CencPssh();
    const std::string& GetPssh() const;

  private:
    std::string pssh_;

    friend class CencPsshElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_CENCPSSH_H_ */
