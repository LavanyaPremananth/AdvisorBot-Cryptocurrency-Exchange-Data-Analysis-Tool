#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <unordered_map>
#include <algorithm>
#include <iostream>


/** construct, reading a csv data file */
OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

/** return vector of all know products in the dataset*/
std::vector<std::string> OrderBook::getKnownProducts(std::string const& currentTime)
{
    std::vector<std::string> products;
    std::unordered_map<std::string, bool> prodMap;

    for (OrderBookEntry& e : orders) {
        if (e.timeStamp == currentTime) {
            prodMap[e.product] = true;
        }
        else if (e.timeStamp > currentTime) {
            break;
        }
    }

    for (auto const& e : prodMap) {
        products.push_back(e.first);
    }

    return products;
}
/** return vector of Orders according to the sent filters*/
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp) {
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e : orders) {
        if (e.timeStamp < timestamp) {
            continue;
        }
        if (e.timeStamp > timestamp) {
            break;
        }
        if (e.orderType == type
            && e.product == product
            && e.timeStamp == timestamp) {
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}


double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;
    for (OrderBookEntry& e : orders)
    {
        if (e.price > max)max = e.price;
    }
    return max;
}


double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
    double min = orders[0].price;
    for (OrderBookEntry& e : orders)
    {
        if (e.price < min)min = e.price;
    }
    return min;
}

double OrderBook::getAvgPrice(std::vector<OrderBookEntry>& orders) {
    double totalOfPrices = 0;
    for (OrderBookEntry& e : orders) {
        totalOfPrices += e.price;
    }

    return totalOfPrices / orders.size();
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timeStamp;
}

std::string OrderBook::getNextTime(std::string timeStamp)
{
    std::string next_timeStamp = "";
    for (OrderBookEntry& e : orders)
    {
        if (e.timeStamp > timeStamp)
        {
            next_timeStamp = e.timeStamp;
            break;
        }
    }
    if (next_timeStamp == "")
    {
        next_timeStamp = orders[0].timeStamp;
    }
    return next_timeStamp;
}
std::string OrderBook::getPrevTime(std::string timestamp) {

    std::string next_timestamp = "";
    for (OrderBookEntry& e : orders) {
        if (e.timeStamp >= timestamp) {
            break;
        }
        else {
            next_timestamp = e.timeStamp;
        }
    }

    return next_timestamp;
}

std::string OrderBook::setCurrentTime(int a) {
    if (a < 1 || a > orders.size()) {
        std::cout << "OrderBook::setCurrentTime Bad input" << std::endl;
        return "";
    }

    std::string currentTimeStamp = orders[0].timeStamp;
    int cnt = 1;
    for (OrderBookEntry& e : orders) {
        if (currentTimeStamp != e.timeStamp) {
            currentTimeStamp = e.timeStamp;
            cnt++;
        }

        if (a == cnt) {
            break;
        }
    }

    return currentTimeStamp;
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string& timestamp) {
    /*
     * The only optimisation I made for this function is to make find matches for every product on the current timestamp
     * and not only one.
     */
     //sales
    std::vector<OrderBookEntry> sales;

    //loop over all products
    std::vector<std::string> products = getKnownProducts(timestamp);
    for (std::string& product : products) {
        //getting vector of asks for product in current time stamp
        std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
        //getting vector of bids for product in current time stamp
        std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);

        //sort asks lowest first
        std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
        //sort bids highest first
        std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

        //loop over all asks and bids to find matches
        for (OrderBookEntry& ask : asks) {
            if (ask.amount == 0) {
                continue;
            }
            for (OrderBookEntry& bid : bids) {
                if (bid.price >= ask.price) {
                    if (bid.amount == 0) {
                        continue;
                    }
                    OrderBookEntry sale{ ask.price, 0, timestamp, product, OrderBookType::asksale };

                    sale.amount = std::min(bid.amount, ask.amount);
                    ask.amount -= sale.amount;
                    bid.amount -= sale.amount;

                    sales.push_back(sale);
                }
            }
        }
    }

    return sales;
}

int OrderBook::getEntriesSize() {
    return orders.size();
}