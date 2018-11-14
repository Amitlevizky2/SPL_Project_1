//
// Created by Amit Levizky on 11/3/18.
//

#include "Table.h"
#include <iostream>

Table::Table(int t_capacity) : capacity(t_capacity), open(false), customersList(), orderList(), totalBill(0) {}

int Table::getCapacity() const {return capacity;}

void Table::addCustomer(Customer *customer) {
    customersList.push_back(customer);//Add Condition
}

void Table::removeCustomer(int id) {
    for (int i = 0; i < customersList.size(); ++i) {
        if(customersList[i]->getId() == id ) {
            customersList.erase(customersList.begin() + i);
        }
        for (int j = 0; j < orderList.size(); ++j) {
            if(orderList[i].first == id) {
                totalBill = totalBill - orderList[i].second.getPrice();
                orderList.erase(orderList.begin() + i);
            }
        }
    }
}

Customer* Table::getCustomer(int id) {
    for (int i = 0; i < customersList.size(); ++i) {
        if (customersList[i]->getId() == id)
            return customersList[i];
    }
    return nullptr;
}

std::vector<Customer*>& Table::getCustomers() {return customersList;}

std::vector<OrderPair>& Table::getOrders() { return orderList;}

void Table::order(const std::vector<Dish> &menu) {
    for (int i = 0; i < customersList.size(); ++i) {
        Customer* currentCustomer = customersList[i];
        std::vector <int> ordrByCtr = currentCustomer[i].order(menu);
        for (int j = 0; j < ordrByCtr.size(); ++j) {
            OrderPair newOrdByCtr(currentCustomer[i].getId(), menu[ordrByCtr[j]]);
            orderList.push_back(newOrdByCtr);
            totalBill = totalBill + menu[ordrByCtr[j]].getPrice();
        }
    }
}

void Table::openTable() {
    open = true;
}

void Table::closeTable() {
    for (int i = 0; i < customersList.size(); ++i) {
        delete customersList[i];
    }
    customersList.clear();
    orderList.clear();
    open=false;
    totalBill = 0;
}

int Table::getBill() { return totalBill;}

bool Table::isOpen() { return open;}