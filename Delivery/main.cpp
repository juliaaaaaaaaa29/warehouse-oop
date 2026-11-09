#include <iostream>
#include <limits>
#include "orderManager.h"
#include "discounts.h"
#include "delivery.h"

int main() {
    setlocale(LC_ALL, "Russian");
    auto manager = std::make_shared<OrderManager>();
    auto electronics = Product::getType("Электроника", 50, 0.7);

    std::shared_ptr<Order> currentOrder = nullptr;
    int choice = -1;

    while (choice != 0) {
        std::cout << "\nМЕНЮ\n";
        std::cout << "1. Создать заказ (Покупатель)\n";
        std::cout << "2. Добавить 1 товар\n";
        std::cout << "3. Добавить 20 товаров \n";
        std::cout << "4. Применить скидку 10%\n";
        std::cout << "5. Назначить доставку (Курьер)\n";
        std::cout << "6. Назначить доставку (Почта)\n";
        std::cout << "7. Назначить доставку (Самовывоз)\n";
        std::cout << "8. Оплатить заказ\n";
        std::cout << "9. Отменить заказ\n";
        std::cout << "10. Показать текущую цену и вес\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода! Введите цифру.\n";
            continue;
        }

        switch (choice) {
        case 1:
            try {
                currentOrder = manager->createOrder("Иван");
                std::cout << "[Менеджер] Заказ создан! ID: " << currentOrder->getId() << "\n";
            }
            catch (const std::exception& e) {
                std::cout << "[Ошибка] " << e.what() << "\n";
            }
            break;
        case 2:
            if (currentOrder) {
                currentOrder->addItem(std::make_shared<Product>(1, 1, electronics->getBasePrice(), electronics));
                std::cout << "[Заказ] Добавлен 1 товар.\n";
            }
            else std::cout << "Сначала создайте заказ!\n";
            break;

        case 3:
            if (currentOrder) {
                currentOrder->addItem(std::make_shared<Product>(1, 1, electronics->getBasePrice(), electronics));
                std::cout << "[Заказ] Добавлено 20 товаров.\n";
            }
            else std::cout << "Сначала создайте заказ!\n";
            break;

        case 4:
            if (currentOrder) {
                PercentDiscount disc;
                *currentOrder + disc; // Перегрузка +
                std::cout << "[Скидка] Применена скидка 10%.\n";
            }
            else std::cout << "Сначала создайте заказ!\n";
            break;

        case 5: 
            if (currentOrder) {
                try {
                    std::shared_ptr<Delivery> proxy = std::make_shared<DeliveryProxy>(std::make_shared<CourierDelivery>());
                    proxy << *currentOrder; 
                    std::cout << "[Доставка] Курьер назначен. Стоимость: " << proxy->getCost(*currentOrder) << " руб.\n";
                }
                catch (const std::exception& e) { std::cout << "Ошибка доставки: " << e.what() << "\n"; }
            }
            else std::cout << "Сначала создайте заказ!\n";
            break;

        case 6:
            if (currentOrder) {
                try {
                    std::shared_ptr<Delivery> proxy = std::make_shared<DeliveryProxy>(std::make_shared<PostDelivery>());
                    proxy << *currentOrder;
                    std::cout << "[Доставка] Почта назначена. Стоимость: " << proxy->getCost(*currentOrder) << " руб.\n";
                }
                catch (const std::exception& e) { std::cout << "Ошибка доставки: " << e.what() << "\n"; }
            }
            else std::cout << "Сначала создайте заказ!\n";
            break;

        case 7: 
            if (currentOrder) {
                try {
                    std::shared_ptr<Delivery> proxy = std::make_shared<DeliveryProxy>(std::make_shared<PickupDelivery>());
                    proxy << *currentOrder;
                    std::cout << "[Доставка] Самовывоз назначен. Стоимость: " << proxy->getCost(*currentOrder) << " руб.\n";
                }
                catch (const std::exception& e) { std::cout << "Ошибка доставки: " << e.what() << "\n"; }
            }
            else std::cout << "Сначала создайте заказ!\n";
            break;

        case 8: 
            if (currentOrder) {
                currentOrder->setStatus(OrderStatus::Paid);
                std::cout << "[Менеджер] Заказ оплачен! Оборот магазина: " << manager->getTurnover() << "\n";
            }
            else std::cout << "Сначала создайте заказ!\n";
            break;

        case 9:
            if (currentOrder) {
                currentOrder->setStatus(OrderStatus::Cancelled);
                std::cout << "[Заказ] Заказ отменен (лимиты освобождены).\n";
            }
            else std::cout << "Сначала создайте заказ!\n";
            break;

        case 10: 
            if (currentOrder) {
                std::cout << "Цена: " << currentOrder->getTotalPrice() << " руб. | Вес: "
                    << currentOrder->getTotalWeight() << " кг\n";
            }
            else std::cout << "Сначала создайте заказ!\n";
            break;

        case 0:
            std::cout << "Выход...\n";
            break;

        default:
            std::cout << "Неверный ввод! Такого пункта нет.\n";
        }
    }

    return 0;
}