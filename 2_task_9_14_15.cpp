#include <iostream>
#include "Money.h"

int main()
{
    Money::Money::init_currency(R"(C:\Users\gutyr\CLionProjects\2_task_9\currency.data)");

    try
    {
        Money::Money amount1;
        Money::Money amount2;

        std::cout << "enter 2 monetary amounts (in currency banknote.coin format: USD 4.55): ";
        std::cin >> amount1 >> amount2;

        std::cout << amount1 << " + " << amount2 << " = " << amount1 + amount2 << std::endl
                  << amount1 << " - " << amount2 << " = " << amount1 - amount2 << std::endl
                  << amount1 << " / " << amount2 << " = " << amount1 / amount2 << std::endl
                  << amount1 << " * 5" << " = " << amount1 * 5 << std::endl;
    }

    catch(Money::Money::currency_is_empty&)
    {
        std::cout << "currency table not initialized" << std::endl;
    }

    return 0;
}

