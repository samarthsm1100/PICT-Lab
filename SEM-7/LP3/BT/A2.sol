// SPDX-License-Identifier: Unlicensed
pragma solidity ^0.8.0;

contract StudentData {
    struct Student {
        string name;
        uint age;
        string major;
    }

    Student[] internal students;

    function addStudent(string memory _name, uint _age, string memory _major) public {
        Student memory newStudent = Student(_name, _age, _major);
        students.push(newStudent);
    }

    function getStudentCount() public view returns (uint) {
        return students.length;
    }

    function getStudent(uint index) public view returns (string memory, uint, string memory) {
        require(index < students.length, "Student does not exist");
        Student memory student = students[index];
        return (student.name, student.age, student.major);
    }

    fallback() external payable {
        // Handle unexpected calls or Ether transfers
    }

    receive() external payable {
        // Handle direct Ether transfers
    }
}
