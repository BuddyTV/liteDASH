/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "failovercontent_element_parser.h"
#include "failovercontent.h"

#include "fcs_element_parser.h"
#include "fcs.h"

#include "utils.h"


namespace dash {
namespace mpd {

bool FailoverContentElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  FailoverContent *elem = static_cast<FailoverContent*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("valid") {
      elem->valid_ = Utils::ConvertToBool(attrib[i + 1]);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* FailoverContentElementParser::CreateElement(
    const std::string &element) const {
  return new FailoverContent();
}

void FailoverContentElementParser::AttachChildElementToParent(
    ElementBase *parent, ElementBase *child) {
  FailoverContent *elem = static_cast<FailoverContent*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "FCS") {
    elem->fcs_.push_back(static_cast<FCS*>(child));
  } else {
    ElementBaseParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* FailoverContentElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "FCS") {
    parser = std::make_unique < FCSElementParser > (name, parent);
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
