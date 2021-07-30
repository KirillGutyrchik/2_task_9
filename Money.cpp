#include <fstream>
#include "Money.h"
#include <limits>
#include <cmath>
#include <utility>



namespace Money
{
    TableCurrency      Money::table_currency;

    Money::Money()
    :currency("USD"),
    coin(0)
    {
        if(table_currency.empty())
        {
            throw currency_is_empty();
        }
    }

    Money::Money(std::string currency, long coin)
            : currency(std::move(currency)),
            coin(coin)
    {}

    Money::Money(const Money &money)
    {
        coin     = money.coin;
        currency = money.currency;
    }

    Money& Money::operator=(const Money &money)
    {
        coin = static_cast<long>( round( static_cast<double>(money.coin) * exchange( currency, money.currency )));
        return *this;
    }

    double Money::exchange(const std::string &currency_1, const std::string &currency_2)
    {
        return Money::table_currency[currency_1] / Money::table_currency[currency_2];
    }



    void Money::init_currency(const std::string &path_file)
    {
        std::string s_currency;
        double factor;

        std::ifstream file_currency(path_file);
        while (!file_currency.eof())
        {
            file_currency >> s_currency >> factor;
            table_currency[s_currency] = factor;
        }
    }


    Money Money::operator+(const Money &money)
    {

        long result_coin = coin + static_cast<long>(round( static_cast<double>( money.coin ) * exchange( this->currency, money.currency )));

        return Money(currency, result_coin);
    }

    Money Money::operator-(const Money &money)
    {
        long result_coin = coin - static_cast<long>( round( static_cast<double>(money.coin) * exchange( currency, money.currency )));

        return Money(currency, result_coin);;
    }

    const Money& Money::operator+=(const Money &money)
    {
        coin += static_cast<long>(round( static_cast<double>( money.coin ) * exchange( currency, money.currency )));
        return *this;
    }

    const Money& Money::operator-=(const Money &money)
    {
        coin += static_cast<long>(round( static_cast<double>( money.coin ) * exchange( currency, money.currency )));
        return *this;
    }

    double Money::operator/ (const Money &money)
    {
        return static_cast<double>(coin) / static_cast<double>(money.coin) / exchange(this->currency, money.currency) ;
    }

    Money Money::operator*(double factor)
    {
        return Money(currency, static_cast<long>(round(static_cast<double >(coin)*factor)));
    }

    const Money& Money::operator*=(double factor)
    {
        coin = static_cast<long>(round(static_cast<double >(coin)*factor));
        return *this;
    }

    const Money& Money::operator/=(double divider)
    {
        coin = static_cast<long>(round(static_cast<double >(coin) / divider));
        return *this;
    }

    std::istream &operator>>(std::istream &input, Money &money)
    {
        double amount;
        while (true) {
            input >> money.currency;
            input >> amount;

            if (input.good() && Money::table_currency.find(money.currency) != Money::table_currency.end()) break;
            std::cout << "Please enter the amount correctly: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }


        money.coin = static_cast<short>( round(amount * 100));

        return input;
    }

    std::ostream &operator<<(std::ostream &output, const Money &money)
    {
        output << money.currency << ' ' << static_cast<double>(money.coin) / 100.0;
        return output;
    }




}