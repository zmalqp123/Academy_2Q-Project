#pragma once
#include <vector>
#include <string>

class Button;
class ImageUIRenderer;
class TextUIRenderer;
class GameObject;
class ramdomReward 
{
public:

	std::vector<Button*>  btns;
	std::vector<ImageUIRenderer*>  Uis;
	std::vector<TextUIRenderer*>  TextNameUis;
	std::vector<TextUIRenderer*>  TextStatUis;
    std::wstring comosusSuggestion[26] = {
        L"훌륭한 파인애플이군, 보상을 말해라.",
        L"훌륭한 파인애플이군, 보상을 말해라.",
        L"훌륭한 파인애플이군, 보상을 말해라.",
        L"훌륭한 파인애플이군, 보상을 말해라.",
        L"훌륭한 파인애플이군, 보상을 말해라.",
        L"추종자여, 더 질 좋은 파인애플을 하사해주마.",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"추종자여, 최고의 파인애플을 하사해주마.",
        L"실망시키지 않는군, 무엇을 원하지?", 
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?"
    };
    
    TextUIRenderer* rewardMoney;
	TextUIRenderer* textHeader;
	std::vector<GameObject*> bgUi;

	ramdomReward() {};
	void shuffle();
	void setValue();
	void UIon();
	void UIoff();
};

