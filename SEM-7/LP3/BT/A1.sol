// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract Bank {
    address public customer;
    uint private balance;

    constructor() {
        customer = msg.sender;
    }

    function deposit() public payable {
        require(msg.sender == customer, "Only the assigned customer can deposit");
        require(msg.value > 0, "Deposit amount must be greater than zero");
        balance += msg.value;
    }

    function withdraw(uint amount) public {
        require(msg.sender == customer, "Only the assigned customer can withdraw");
        require(amount > 0, "Withdrawal amount must be greater than zero");
        require(balance >= amount, "Insufficient balance");
        balance -= amount;
        payable(customer).transfer(amount);
    }

    function getBalance() public view returns (uint) {
        require(msg.sender == customer, "Only the assigned customer can check balance");
        return balance;
    }
}