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
        L"피와 햇빛, 좋은 파인애플의6 조건이지.",
        L"피와 햇빛, 좋은 파인애플의 조건이지.",
        L"더 달콤한 파인애플이 필요하다!",
        L"추종자여, 더 좋은 파인애플을 하사해주마.",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"실망시키지 않는군, 무엇을 원하지?",
        L"추종자여, 최고의 파인애플을 하사해주마.",
        L"천상의 맛이야! 보답을 말해라!",
        L"천상의 맛이야! 보답을 말해라!",
        L"천상의 맛이야! 보답을 말해라!",
        L"천상의 맛이야! 보답을 말해라!",
        L"우주를 돌아다니다 우연히 파인애플을 만났지.",
        L"너무나 달콤하고, 매력적인 생김새였어.",
        L"지구는… 파인애플을 기르기 최고의 환경이었다.",
        L"추종자들을 시켜 파인애플을 바치게 했다.",
        L"하지만 이젠 인내심의 한계야. 더 많은 걸 원해.",
        L"그래서 직접 찾아가기로 결심했다네.",
        L"구원자들을 제외한 나머지는 살 가치가 없어",
        L"양분으로 만들어 파인애플의 비료로 써주마.",
        L"파인애플, 내가 찾아가마!",
        L"파인애플! 파인애플!!!",
        L"파인애플! 파인애플!!!"
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

