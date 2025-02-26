#include <iostream>
#include "ExpressionSolver.hpp"
#include "NotPuzzle.hpp"

int main(int argc, char **argv) {
	setlocale(LC_ALL, "Russian");
	NotPuzzle::NotPuzzleTaskManager task_manager;
	task_manager.attemptTask();

	return 0;
}