//
//  LabelBBCode.h
//  Casino
//
//  Created by Quan Nguyen on 4/20/17.
//
//

#ifndef LabelBBCode_h
#define LabelBBCode_h

#include "cocos2d.h"

namespace bbcpp
{
    class BBNode;
}

class LabelBBCode : public cocos2d::Label {
public:
    typedef std::function<void(LabelBBCode *sender, const std::string& url)> HrefCallback;
    
public:
    LabelBBCode();
    virtual ~LabelBBCode();
    
    static LabelBBCode* create(const std::string& text, float fontSize);
    static cocos2d::Color3B getColorFromHex(const std::string& hexColorString);
    
    void doEffect(const bbcpp::BBNode& node, int nowIdx);
    void doEffectColor(const bbcpp::BBNode& node, int& nowIdx, const cocos2d::Color3B& color);
    void doEffectBold(const bbcpp::BBNode& node, int& nowIdx);
    void doEffectItalic(const bbcpp::BBNode& node, int& nowIdx);
    void doEffectUnderline(const bbcpp::BBNode& node, int& nowIdx);
    void doEffectHyperLink(const bbcpp::BBNode& node, int& nowIdx);
    
protected:
    CC_SYNTHESIZE_PASS_BY_REF(HrefCallback, _hrefCallback, HrefCallback);
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _originalText, OriginalText);
};

#endif /* LabelBBCode_h */
