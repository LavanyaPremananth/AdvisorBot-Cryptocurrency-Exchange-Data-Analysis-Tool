#pragma once

#include <string>

enum class OrderBookType { bid, ask, unknown, asksale, bidsale };

class OrderBookEntry
{
public:


    OrderBookEntry(double _price,
        double _amount,
        std::string _timeStamp,
        std::string _product,
        OrderBookType _orderType,
        std::string username = "dataset");

    static OrderBookType stringToOrderBookType(std::string s);

    static bool compareBytimeStamp(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.timeStamp < e2.timeStamp;
    }
    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.price < e2.price;
    }
    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.price > e2.price;
    }

    double price;
    double amount;
    std::string timeStamp;
    std::string product;
    OrderBookType orderType;
    std::string username;
};
