//
//  LabelXML.hpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/5.
//
//

#ifndef LabelXML_hpp
#define LabelXML_hpp

#include "CocoSupport.h"

struct T_LableParams {
    Color3B color;
    int     size;
    string  text;
    string  font;
    string  bmfont;
    
    T_LableParams() {
        color   = Color3B::WHITE;
        size    = 18;
        text    = "";
        font    = DEFAULT_FONT;
        bmfont  = "";
    }
};

struct T_RowCol {
    unsigned int row = 0;
    unsigned int col = 0;
    T_RowCol(unsigned int _row, unsigned int _col) {
        row = _row;
        col = _col;
    }
};

class LabelXML : public Label {
private:
    Layout*         m_pContainerNode;       //节点容器
    vector<Label*>  m_vecAllLabelNodes;     //存储所有节点
    unsigned int    m_nMaxWidth;            //允许的最大宽度
    unsigned int    m_nCharSpace;           //字符间距
    unsigned int    m_nLineSpace;           //行间距
    string          m_sXmlString;           //当前文本内容
    bool            m_bIsValidXml;          //是否有效
public:
    LabelXML(string xml);
    ~LabelXML();
    
    // 设置,获取文本内容
    void setXmlString(string xml);
    void getXmlString();
    
    // 文本重排
    void doLayout();
    
    // 最大宽度
    void setMaxWidth(unsigned int maxwidth);
    inline int getMaxWidth() { return m_nMaxWidth; }
    
    // 间距
    void setCharSpace(unsigned int space);
    inline int getCharSpace() { return m_nCharSpace; }
    void setLineSpace(unsigned int space);
    inline int getLineSpace() { return m_nLineSpace; }
    
    // 动画
    void playAnimation();
    void stopAnimation();
private:
    void _parseXmlString();
};

#endif /* LabelXML_hpp */
