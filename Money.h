#pragma once
#include <iostream>
#include <map>
#include <string>

namespace Money
{
    using TableCurrency = std::map<std::string, double>;

    class Money final
    {
    private:
        static TableCurrency table_currency;

        std::string currency;
        long coin;


    private:
        Money(std::string currency, long coin);
        static long exchange(long coin, const std::string& currency_1, const std::string& currency_2);

    public:
        class currency_is_empty : std::exception
        {};

        Money();
        Money(const Money& money);
        Money& operator= (const Money& money);

        static void init_currency(const std::string& path_file);

        Money operator+ (const Money& money);
        Money operator- (const Money& money);
        const Money& operator+= (const Money& money);
        const Money& operator-= (const Money& money);
        double operator/ (const Money& money);
        Money operator* (double factor);
        const Money& operator*=(double factor);
        const Money& operator/=(double divider);

        friend std::istream &operator>>(std::istream &input, Money &money);
        friend std::ostream &operator<<(std::ostream &output, const Money &money);
    };
}