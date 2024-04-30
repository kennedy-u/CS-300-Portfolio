//////////////////////////////////
// Created by Kennedy Uzoho.
//////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex> 
#include "Models/Courses.h"

/**
 * Display the course information to the console (std::cout)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
	std::vector<std::string> coursePrerequisites = course.getCoursePrerequisites();
	std::string prerequisites;
	// formats output for prerequisites, if there are any
	if (coursePrerequisites.size() == 1) {
		prerequisites = course.getCoursePrerequisites()[0];
	} else if (coursePrerequisites.size() > 1) {
		for (int i = 0; i < coursePrerequisites.size() - 1; i++) {
			prerequisites += coursePrerequisites[i] + ", ";
		}
		prerequisites += coursePrerequisites.back();
	} else {
		prerequisites = "n/a";
	}

	// prints out the course details
	std::cout << course.getCourseId() << ", "
			  << course.getCourseName() << std::endl;
	std::cout << "Prerequisites: " << prerequisites << std::endl;
}

/**
 * Load an input file containing courses into a container
 *
 * @param inputFilePath the path to the input file to load
 * @return a container holding all the courses read
 */

void loadCourses(Courses* coursesBst) {
	std::string inputFilePath = "C:\\Users\\Kenyk\\Desktop\\SNHUCompsci\\CS-300-Portfolio\\CS-300-Portfolio\\ABCU_Advising_Program_Input.txt"; // replace with your file path
	std::cout << "Loading input file " << std::endl;

	std::ifstream file(inputFilePath);
	std::string currentLine;
	try {
		while (std::getline(file, currentLine)) {
			std::stringstream ss(currentLine);
			std::string word, id, name;
			std::vector<std::string> prerequisites;
			int index = 0;
			while (!ss.eof()) {
				getline(ss, word, ',');
				word = std::regex_replace(word, std::regex(R"(\r\n|\r|\n)"), "");
				if (index == 0) {
					id = word;
				}
				else if (index == 1) {
					name = word;
				}
				else {
					prerequisites.push_back(word);
				}
				index++;
			}
			// create a data structure and add to the collection of courses
			Course course = Course(id, name, prerequisites);
			// add this course to the tree
			coursesBst->Insert(course);
		}
	}
	catch (std::ifstream::failure& e) {
		std::cerr << e.what() << std::endl;
	}

	file.close();
}

int main() {
	// Define a binary search tree to hold all courses
	Courses* coursesBst;
	coursesBst = new Courses();
	Course course;
	std::string courseKey;

	std::cout << "Welcome to the course planner." << std::endl << std::endl;

	int choice = 0;
	while (choice != 9) {
		std::cout << "  1. Load Data Structure" << std::endl;
		std::cout << "  2. Print Course List" << std::endl;
		std::cout << "  3. Print Course" << std::endl;
		std::cout << "  9. Exit" << std::endl << std::endl;
		std::cout << "What would you like to do? ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			// Load the courses without asking for the file path
			loadCourses(coursesBst);
			break;
		case 2:
			std::cout << "Here is a sample schedule:" << std::endl << std::endl;
			coursesBst->InOrder();
			break;
		case 3:
			std::cout << "What course do you want to know about? ";
			std::cin >> courseKey;
			course = coursesBst->Search(courseKey);

			if (!course.getCourseId().empty()) {
				displayCourse(course);
			}
			else {
				std::cout << "Course Id " << courseKey << " not found." << std::endl;
			}
			break;
		case 9:
			std::cout << "Good bye." << std::endl;
			break;
		default:
			std::cout << choice << " is not a valid option." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
		std::cout << std::endl;
	}

	return 0;
}