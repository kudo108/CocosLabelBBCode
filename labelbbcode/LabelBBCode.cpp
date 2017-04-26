//
//  LabelBBCode.cpp
//  Casino
//
//  Created by Quan Nguyen on 4/20/17.
//
//

#include "LabelBBCode.h"
#include "BBDocument.h"

USING_NS_CC;

LabelBBCode::LabelBBCode()
: _hrefCallback(nullptr)
{
    
}

LabelBBCode::~LabelBBCode()
{
    
}

LabelBBCode* LabelBBCode::create(const std::string &text, float fontSize)
{
    //format the text
    auto doc = bbcpp::BBDocument::create();
    doc->load(text);
#if COCOS2D_DEBUG > 0
    bbcpp::printDocument(*doc);
#endif
    std::string rawText = bbcpp::getRawString(*doc);
    CCLOG("LabelBBCode: raw = %s", rawText.c_str());
    
    auto lb = new LabelBBCode();
    if(lb && lb->initWithTTF(rawText, "Roboto-Bold.ttf", fontSize)){
        lb->autorelease();
        lb->setOriginalText(text);
        
        lb->doEffect(*doc, 0);
        
        return lb;
    }
    CC_SAFE_DELETE(lb);
    return nullptr;
}

void LabelBBCode::doEffect(const bbcpp::BBNode& parent, int nowIdx)
{
    int idx = nowIdx;
    Color3B color = Color3B::WHITE;
    
    //edit lb do set effect
    for (const auto node : parent.getChildren())
    {
        switch (node->getNodeType())
        {
            default:
                break;
                
            case bbcpp::BBNode::ELEMENT:
            {
                const auto element = node->downCast<bbcpp::BBElementPtr>();
                
                if (element->getElementType() == bbcpp::BBElement::PARAMETER)
                {
                    auto params = element->getParameters();
                    auto colorFind = params.find("color");
                    if(colorFind == params.end()){
                        //dont have color parameter
                    }else{
                        std::string value = colorFind->second;
                        color = getColorFromHex(value);
                        int idx2 = idx;
                        doEffectColor(*node, idx2, color);
                        
                        idx = MAX(idx, idx2);
                    }
                    
                }
                else if(element->getElementType() == bbcpp::BBElement::CLOSING){
                    //end of color
                    if(node->getNodeName() == "color"){
                    }
                }
                else if (element->getElementType() == bbcpp::BBElement::SIMPLE){
                    if(node->getNodeName() == "b"){
                        //bold
                        int idx2 = idx;
                        doEffectBold(*node, idx2);
                        
                        idx = MAX(idx2, idx);
                    }else if (node->getNodeName() == "i"){
                        //italic
                        int idx2 = idx;
                        doEffectItalic(*node, idx2);
                        
                        idx = MAX(idx2, idx);
                    }else if (node->getNodeName() == "u"){
                        //under line
                        int idx2 = idx;
                        doEffectUnderline(*node, idx2);
                        
                        idx = MAX(idx2, idx);
                    }
                }
            }
                break;
                
            case bbcpp::BBNode::TEXT:
            {
                const auto textnode = node->downCast<bbcpp::BBTextPtr>();
                std::string text = textnode->getText();
                
                std::u32string utf32String;
                StringUtils::UTF8ToUTF32(text, utf32String);
                int length = utf32String.length();
                idx += length;
            }
                break;
        }
        
        doEffect(*node, idx);
    }
}

void LabelBBCode::doEffectColor(const bbcpp::BBNode &parent, int& idx, const cocos2d::Color3B &color)
{
    for (const auto node : parent.getChildren())
    {
        switch (node->getNodeType())
        {
            default:
                break;
                
            case bbcpp::BBNode::ELEMENT:
            {
            }
                break;
                
            case bbcpp::BBNode::TEXT:
            {
                const auto textnode = node->downCast<bbcpp::BBTextPtr>();
                std::string text = textnode->getText();
                
                std::u32string utf32String;
                StringUtils::UTF8ToUTF32(text, utf32String);
                int length = utf32String.length();
                
                //update effect color
                for(int i = 0; i < length; i ++){
                    int realIdx = i + idx;
                    Sprite *sp = this->getLetter(realIdx);
                    sp->setColor(color);
                }
                
                idx += length;
            }
                break;
        }
        
        doEffectColor(*node, idx, color);
    }
}

void LabelBBCode::doEffectBold(const bbcpp::BBNode &parent, int &idx)
{
    for (const auto node : parent.getChildren())
    {
        switch (node->getNodeType())
        {
            default:
                break;
                
            case bbcpp::BBNode::ELEMENT:
            {
            }
                break;
                
            case bbcpp::BBNode::TEXT:
            {
                const auto textnode = node->downCast<bbcpp::BBTextPtr>();
                std::string text = textnode->getText();
                
                std::u32string utf32String;
                StringUtils::UTF8ToUTF32(text, utf32String);
                int length = utf32String.length();
                
                //update effect color
                for(int i = 0; i < length; i ++){
                    int realIdx = i + idx;
                    //TODO: do bold
                }
                
                idx += length;
            }
                break;
        }
        
        doEffectBold(*node, idx);
    }
}

void LabelBBCode::doEffectItalic(const bbcpp::BBNode &parent, int &idx)
{
    for (const auto node : parent.getChildren())
    {
        switch (node->getNodeType())
        {
            default:
                break;
                
            case bbcpp::BBNode::ELEMENT:
            {
            }
                break;
                
            case bbcpp::BBNode::TEXT:
            {
                const auto textnode = node->downCast<bbcpp::BBTextPtr>();
                std::string text = textnode->getText();
                
                std::u32string utf32String;
                StringUtils::UTF8ToUTF32(text, utf32String);
                int length = utf32String.length();
                
                //update effect color
                for(int i = 0; i < length; i ++){
                    int realIdx = i + idx;
                    //TODO: do bold
                }
                
                idx += length;
            }
                break;
        }
        
        doEffectItalic(*node, idx);
    }
}

void LabelBBCode::doEffectUnderline(const bbcpp::BBNode &parent, int &idx)
{
    for (const auto node : parent.getChildren())
    {
        switch (node->getNodeType())
        {
            default:
                break;
                
            case bbcpp::BBNode::ELEMENT:
            {
            }
                break;
                
            case bbcpp::BBNode::TEXT:
            {
                const auto textnode = node->downCast<bbcpp::BBTextPtr>();
                std::string text = textnode->getText();
                
                std::u32string utf32String;
                StringUtils::UTF8ToUTF32(text, utf32String);
                int length = utf32String.length();
                
                //update effect color
                for(int i = 0; i < length; i ++){
                    int realIdx = i + idx;
                    //TODO: do bold
                }
                
                idx += length;
            }
                break;
        }
        
        doEffectUnderline(*node, idx);
    }
}

void LabelBBCode::doEffectHyperLink(const bbcpp::BBNode &parent, int &idx)
{
    //do action
}

#pragma mark - utils

Color3B LabelBBCode::getColorFromHex(const std::string& hexColorString1)
{
    std::string hexColorString = hexColorString1;
    if(hexColorString.length() == 0){
        return Color3B::WHITE;
    }
    if(hexColorString.at(0) == '#'){
        hexColorString = hexColorString.substr(1, 6);
    }
    std::stringstream str;
    str<<hexColorString;
    int hexValue;
    str>> std::hex >> hexValue;
    
    float red       = (hexValue & 0xff0000) >> 16;
    float green     = (hexValue & 0x00ff00) >> 8;
    float blue      = (hexValue & 0x0000ff) ;
    
    return Color3B(red, green, blue);
}
