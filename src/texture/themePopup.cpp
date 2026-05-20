#include "texture.hpp"

using namespace geode::prelude;

bool theme::SelectPopup::init() {
    if (!Popup::init(400.f, 280.f, "geode.loader/GE_square02.png"))
        return false;

    this->setTitle("Select a Theme");

    // VISUALIZER theme
    this->m_visualizerLabel = CCLabelBMFont::create("Visualizer by MaskaGD", "bigFont.fnt");
    this->m_visualizerLabel->setScale(0.5f);
    this->m_mainLayer->addChildAtPosition(this->m_visualizerLabel, Anchor::Top, { 0.f, -40.f });

    this->m_visualizerPreview = texture::createSprite("gl.maskagd_prev");
    this->m_visualizerPreview->setScale(0.9f);
    this->m_mainLayer->addChildAtPosition(this->m_visualizerPreview, Anchor::Center);
    

    // STANDARD theme
    this->m_standardLabel = CCLabelBMFont::create("Standard by RobTop", "bigFont.fnt");
    this->m_standardLabel->setScale(0.5f);
    this->m_mainLayer->addChildAtPosition(this->m_standardLabel, Anchor::Top, { 0.f, -40.f });

    this->m_standardPreview = texture::createSprite("gl.robtop_prev");
    this->m_standardPreview->setScale(0.9f);
    this->m_mainLayer->addChildAtPosition(this->m_standardPreview, Anchor::Center);


    this->updateVisibility(theme::getCurrentTheme());

    auto arrowBackSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");

    auto arrowNextSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
    arrowNextSpr->setFlipX(true);

    auto arrowBackBtn = CCMenuItemSpriteExtra::create(
        arrowBackSpr, this, menu_selector(theme::SelectPopup::changeTheme)
    );

    auto arrowNextBtn = CCMenuItemSpriteExtra::create(
        arrowNextSpr, this, menu_selector(theme::SelectPopup::changeTheme)
    );

    m_buttonMenu->addChildAtPosition(arrowBackBtn, Anchor::Left, { 25.f, 0.f });
    m_buttonMenu->addChildAtPosition(arrowNextBtn, Anchor::Right, { -25.f, 0.f });


    auto applySpr = ButtonSprite::create("Apply", "goldFont.fnt", "geode.loader/GE_button_05.png", 0.6f);
    setCloseButtonSpr(applySpr);

    m_closeBtn->updateAnchoredPosition(Anchor::Bottom, { 0.f, 25.f });

    return true;
}

void theme::SelectPopup::updateVisibility(theme::Themes currentTheme) {
    this->m_visualizerLabel->setVisible(currentTheme == theme::Themes::Visualizer);
    this->m_visualizerPreview->setVisible(currentTheme == theme::Themes::Visualizer);

    this->m_standardLabel->setVisible(currentTheme == theme::Themes::Standard);
    this->m_standardPreview->setVisible(currentTheme == theme::Themes::Standard);
}

void theme::SelectPopup::changeTheme(CCObject* sender) {
    auto currentTheme = theme::getCurrentTheme();
    
    switch (currentTheme) {
        case theme::Themes::Visualizer:
            theme::changeTheme(theme::Themes::Standard);
            this->updateVisibility(theme::Themes::Standard);
            break;
    
        case theme::Themes::Standard:
            theme::changeTheme(theme::Themes::Visualizer);
            this->updateVisibility(theme::Themes::Visualizer);
            break;
    }
}

theme::SelectPopup* theme::SelectPopup::create() {
    auto ret = new SelectPopup();

    if (ret->init()) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}
