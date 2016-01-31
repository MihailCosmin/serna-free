// 
// Copyright(c) 2009 Syntext, Inc. All Rights Reserved.
// Contact: info@syntext.com, http://www.syntext.com
// 
// This file is part of Syntext Serna XML Editor.
// 
// COMMERCIAL USAGE
// Licensees holding valid Syntext Serna commercial licenses may use this file
// in accordance with the Syntext Serna Commercial License Agreement provided
// with the software, or, alternatively, in accorance with the terms contained
// in a written agreement between you and Syntext, Inc.
// 
// GNU GENERAL PUBLIC LICENSE USAGE
// Alternatively, this file may be used under the terms of the GNU General 
// Public License versions 2.0 or 3.0 as published by the Free Software 
// Foundation and appearing in the file LICENSE.GPL included in the packaging 
// of this file. In addition, as a special exception, Syntext, Inc. gives you
// certain additional rights, which are described in the Syntext, Inc. GPL 
// Exception for Syntext Serna Free Edition, included in the file 
// GPL_EXCEPTION.txt in this package.
// 
// You should have received a copy of appropriate licenses along with this 
// package. If not, see <http://www.syntext.com/legal/>. If you are unsure
// which license is appropriate for your use, please contact the sales 
// department at sales@syntext.com.
// 
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
// 
#ifndef GROVE_VALIDATION_COMMANDS_MAKER_H_
#define GROVE_VALIDATION_COMMANDS_MAKER_H_

#include "grove/grove_defs.h"

namespace Common {
    class PropertyNode;
}

namespace GroveLib {
    
class Node;
class Element;

class ValidationCommandsMaker {
public:
    virtual void    insertNode(Node* before, Node* parent, Node* node) = 0;
    virtual void    removeNode(Node* node) = 0;
    virtual void    setAttributes(Element* elem,
                                  const Common::PropertyNode* specs) = 0;
    virtual ~ValidationCommandsMaker() {}
};

class NullValidationCommandsMaker : public ValidationCommandsMaker {
public:
    virtual void    insertNode(Node*, Node*, Node*) {}
    virtual void    removeNode(Node*) {}
    virtual void    setAttributes(Element*, const Common::PropertyNode*) {}
    virtual ~NullValidationCommandsMaker() {}
};

class RequiredAttributesProvider {
public:
    virtual void fillAttributeValues(const Common::PropertyNode* inSpecs,
                                     Common::PropertyNode* outSpecs,
                                     const Element* elem) const = 0;
    virtual ~RequiredAttributesProvider() {}
};

} // namespace GroveLib

#endif // GROVE_VALIDATION_COMMANDS_MAKER_H_
