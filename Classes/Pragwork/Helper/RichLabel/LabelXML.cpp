//
//  LabelXML.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/5.
//
//

#include "LabelXML.hpp"
#include "XmlParser.hpp"
#include "ActionDefine.h"

LabelXML::LabelXML(string xml)
: m_sXmlString(xml)
, m_nMaxWidth(0)
, m_nCharSpace(0)
, m_nLineSpace(0)
, m_bIsValidXml(false)
, m_pContainerNode(NULL)
{
    m_pContainerNode = new Layout();
    m_pContainerNode->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    m_pContainerNode->setBackGroundColor(Color3B("00ffff"));
    m_pContainerNode->setBackGroundColorOpacity(50);
    addChild(m_pContainerNode);
    
    _parseXmlString();
    doLayout();
}

LabelXML::~LabelXML() {}

void LabelXML::_parseXmlString() {
    XMLDocument* doc = XmlParser::getInstance()->GetDocumentFromString(m_sXmlString.c_str());
    if( !doc ) {
        m_bIsValidXml = false;
        return;
    }
    
    m_bIsValidXml = true;
    m_vecAllLabelNodes.clear();
    
    vector<T_LableParams*> vecLabelParams;
    vecLabelParams.clear();
    
    XMLElement* root = doc->RootElement();
    for( XMLNode* node = root->FirstChild(); node; node = node->NextSibling() ) {
        XMLElement* ele = node->ToElement();
        if(!ele) continue;
        
        T_LableParams* params = new T_LableParams();
        if(ele->Attribute("color")) {
            params->color = Color3B(ele->Attribute("color"));
        }
        if(ele->Attribute("size")) {
            params->size = ele->IntAttribute("size");
        }
        if(ele->Attribute("font")) {
            params->font = ele->Attribute("font");
        }
        if(ele->Attribute("bmfont")) {
            params->bmfont = ele->Attribute("bmfont");
        }
        if(ele->Attribute("text")) {
            cocos2d::StringUtils::StringUTF8::CharUTF8Store text0 = StringUTF8(ele->Attribute("text")).getString();
            if(text0.size() == 0) continue;
            for (int i=0; i<text0.size(); i++) {
                T_LableParams* params_node = new T_LableParams();
                params_node->color = params->color;
                params_node->size  = params->size;
                params_node->font  = params->font;
                params_node->bmfont= params->bmfont;
                string temp = text0.at(i)._char;
                temp.insert(temp.size(), '\0', 1);
                params_node->text  = temp;
                vecLabelParams.push_back(params_node);
            }
        }
    }

    vector<T_LableParams*>::iterator iter = vecLabelParams.begin();
    for(; iter != vecLabelParams.end(); iter++) {
        if( (*iter)->bmfont.empty() ) {
            Label* node = Label::createWithTTF((*iter)->text, (*iter)->font, (*iter)->size);
            if(!node) continue;
            node->setAnchorPoint(Vec2(0,0.5));
            node->setColor((*iter)->color);
            m_pContainerNode->addChild(node);
            m_vecAllLabelNodes.push_back(node);
        } else {
            Label* node = Label::createWithBMFont((*iter)->bmfont, (*iter)->text);
            if(!node) continue;
            node->setBMFontSize((*iter)->size);
            node->setAnchorPoint(Vec2(0,0.5));
            node->setColor((*iter)->color);
            m_pContainerNode->addChild(node);
            m_vecAllLabelNodes.push_back(node);
        }
    }
}


void LabelXML::setXmlString(string xml) {
    if(m_sXmlString == xml) return;
    
    m_pContainerNode->removeAllChildren();
    m_vecAllLabelNodes.clear();
    
    m_sXmlString = xml;
    _parseXmlString();
    
    doLayout();
}

void LabelXML::setMaxWidth(unsigned int maxwidth) {
    if(maxwidth == m_nMaxWidth) return;
    m_nMaxWidth = maxwidth;
}

void LabelXML::setCharSpace(unsigned int space) {
    if(m_nCharSpace == space) return;
    m_nCharSpace = space;
}

void LabelXML::setLineSpace(unsigned int space) {
    if(m_nLineSpace == space) return;
    m_nLineSpace = space;
}

void LabelXML::doLayout() {
    if(m_vecAllLabelNodes.size() == 0) return;
    
    if(m_nMaxWidth == 0) {
        // 单行,优化点:可以不需要按每个字符生成节点
        float width = .0f, height = .0f;
        vector<Label*>::iterator iter = m_vecAllLabelNodes.begin();
        for(; iter != m_vecAllLabelNodes.end(); iter++ ) {
            const Size size = (*iter)->getContentSize();
            width += (size.width + m_nCharSpace);
            if(height < size.height) {
                height = size.height;
            }
        }
        m_pContainerNode->setContentSize(Size(width, height));
        
        iter = m_vecAllLabelNodes.begin();
        float px =.0f;
        for(; iter != m_vecAllLabelNodes.end(); iter++ ) {
            (*iter)->setPosition(px, height*.5f);
            float width = (*iter)->getContentSize().width;
            px += width+m_nCharSpace;
//            CCLOG("[%d] x: %d w: %d", ++id, int(px), int(width));
        }
    } else {
        // 多行
        float width = .0f, height = .0f;
        unsigned int row = 0, col = 0;
        vector< pair<Label*, T_RowCol> > vecPairAllLabelNodes; //存储每行节点
        vector<float> vecLineHeight;
        
        vector<Label*>::iterator iter = m_vecAllLabelNodes.begin();
        for(; iter != m_vecAllLabelNodes.end(); iter++ ) {
            const Size size = (*iter)->getContentSize();
            width += (size.width + m_nCharSpace);
            if(height < size.height) {
                height = size.height;
            }
            
            if(width < m_nMaxWidth) {
                vecPairAllLabelNodes.push_back(make_pair((*iter), T_RowCol(row, col)));
            } else {
                vecLineHeight.push_back(height);
                vecPairAllLabelNodes.push_back(make_pair((*iter), T_RowCol(row+1, col)));
                row++;
                width = 0;
                col = 0;
                height = 0;
            }
            col++;
        }
        vecLineHeight.push_back(height);
        
        int realheight = 0;
        for(int i=0; i<vecLineHeight.size(); i++) {
            realheight += (vecLineHeight.at(i) + m_nLineSpace);
            CCLOG("[%d] height: %f", i, vecLineHeight.at(i));
        }
        
        m_pContainerNode->setContentSize(Size(m_nMaxWidth, realheight));
        m_pContainerNode->setPosition(Vec2(0,0));
        
        vector< pair<Label*, T_RowCol> >::iterator iterMap = vecPairAllLabelNodes.begin();
        float px =.0f, py=realheight;
        int curRow = 0;
        for(; iterMap != vecPairAllLabelNodes.end(); iterMap++ ) {
            Label* pLabel = (*iterMap).first;
            T_RowCol   rc = (*iterMap).second;
            float tempx = px;
            float curheight = vecLineHeight.at(curRow);
            px += pLabel->getContentSize().width + m_nCharSpace;
            if( curRow < rc.row) {
                tempx = 0;
                px = pLabel->getContentSize().width + m_nCharSpace;
                if(curRow > vecLineHeight.size()) break;
                py -= (curheight + m_nLineSpace);
                curRow++;
            }
            pLabel->setPosition(tempx, py-curheight*.5f);
        }
        
    }
}


void LabelXML::playAnimation() {
    for (int i=0; i<m_vecAllLabelNodes.size(); i++) {
        m_vecAllLabelNodes.at(i)->setVisible(false);
        m_vecAllLabelNodes.at(i)->runAction(Sequence::create(DelayTime::create(i*.25f), Show::create(), getActionByCode(ActionCode::EnterBaseFrame), NULL) );
    }
}

void LabelXML::stopAnimation() {
    
}
