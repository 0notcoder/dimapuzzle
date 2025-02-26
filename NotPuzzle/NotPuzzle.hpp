#pragma once

#include "ExpressionSolver.hpp"
#include <memory>
#include <map>
#include <ctime>
#include <deque>
#include <vector>
#include <functional>
#include <iostream>
#include <Windows.h>
#include <random>

namespace NotPuzzle {
	extern enum class taskType;
	static std::map<int, std::string> operators {
		{0, "+"},
		{1, "-"},
		{2, "*"},
		{3, "/"},
		{4, "^"}
	};

	// Дима сам придумай у меня фантазия ебанутая
	static std::vector<std::pair<std::string, std::string>> voprosOtvetNaMillion{
		{"Сколько у обезьяны ушей?", "1"},
		{"Сколько см у админа", "999"}
	};

	constexpr int maxMathTaskLenght{ 4 };
	constexpr int maxMathTaskNumber{ 25 };
	constexpr int maxAttemptsBeforeBanNahuj{ 10 };

	int getRandom(const int &max, const bool &sign);
	std::string getStringFromDeque(const std::deque<std::string> deq);
	void pizdato();
	
	class Task {
	protected:
		std::deque<std::string> m_taskForParser;
		std::string m_taskForUser;
		std::string m_correctAnswer;
	public:
		Task() : m_taskForUser(), m_correctAnswer(), m_taskForParser() {};
		Task(const std::deque<std::string> &taskForParser) :
			m_taskForParser(taskForParser), m_taskForUser(), m_correctAnswer() {};
		
		std::deque<std::string> getTaskForParser() const;
		std::string getTaskForUser() const;
		std::string getCorrectAnswer() const;
	};

	class MathTask : public Task {
	public:
		MathTask();
	};
	class VoprosNaMillion: public Task {
	public:
		VoprosNaMillion();
	};

	class NotPuzzleTaskManager {
	private:
		NotPuzzle::taskType m_taskType;
		std::shared_ptr<Task> m_task;
		int attempts = 0;

	public:
		NotPuzzleTaskManager();
		void attemptTask();

	private:
		std::shared_ptr<Task> getTask() const;
		void generateTask();
	};

};