#pragma once
#include "Layer.h"
#include "../Utils/GameMode.h"
#include "../Drawables/Button.h"

////////////////////////////////////////////////////////////
// Warstwa, kt�ra wy�wietla przyciski w menu.
////////////////////////////////////////////////////////////
class MenuUILayer : public Layer {
public:
	MenuUILayer(Resources*);

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� funkcj�, kt�ra zostanie wywo�ana po
	// wybraniu trybu gry. Paramtrem b�dzie wybrany tryb.
	////////////////////////////////////////////////////////////
	void setOnClickListener(std::function<void(GameMode)>);

private:
	std::vector<Button*> buttons;
	std::function<void(GameMode)> onClickListener;
};