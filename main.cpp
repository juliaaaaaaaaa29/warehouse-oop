#include <iostream>
#include <locale>
#include "Warehouse.h"
#include "ProductFactory.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "1. Создание и добавление\n";
    Warehouse shop(5); 

    SmartphoneFactory phoneMaker;
    MilkFactory milkMaker;
    TShirtFactory tshirtMaker;

    shop.addProduct(phoneMaker.createProduct("iPhone 15", 100000, 5, 0.2));
    shop.addProduct(milkMaker.createProduct("Молоко", 8000, 10, 1.0));
    shop.addProduct(tshirtMaker.createProduct("Футболка", 2000, 20, 0.15));

    std::cout << "Изначально добавлено товаров: " << shop.size() << "\n";
    std::cout << "Вывод списка через итератор \n";

    WarehouseIterator it = shop.begin();
    WarehouseIterator end = shop.end();

    while (it != end) {
        it->describe();
        ++it; 
    }
    std::cout << "\n 2. Копирование склада\n";

    Warehouse backup = shop;
    std::cout << "Создана копия склада.\n";

    Product* phoneInBackup = backup.findById(1);
    if (phoneInBackup) {
        std::cout << "Меняем цену и количество телефона в КОПИИ\n";
        phoneInBackup->setPrice(Price(90000)); 
        phoneInBackup->changeQuantity(-2);     
    }

    std::cout << "\nПроверка ОРИГИНАЛА (shop)\n";
    Product* phoneInOriginal = shop.findById(1);
    if (phoneInOriginal) {
        phoneInOriginal->describe();
    }

    std::cout << "\n Проверка КОПИИ\n";
    if (phoneInBackup) {
        phoneInBackup->describe();
    }
    std::cout << "\n 3. Перемещение склада\n";

    std::cout << "Размер ДО перемещения: " << backup.size() << "\n";
    std::cout << "Выполняем\n";

    Warehouse movedShop = std::move(backup);

    std::cout << "Размер (новый склад): " << movedShop.size() << "\n";
    std::cout << "Размер  (старый склад): " << backup.size() << "\n";

    if (backup.size() == 0) {
        std::cout << "УСПЕХ: Перемещение сработало без копирования (старый склад пуст)!\n";
    }
    else {
        std::cout << "ОШИБКА: Данные скопировались, а не переместились!\n";
    }
    std::cout << "\n 4: Поиск и удаление\n";

    std::cout << "Размер склада до удалений: " << shop.size() << "\n";

    auto food = shop.findByCategory("еда");
    std::cout << "Поиск по категории еда: найдено " << food.size() << " шт.\n";

    auto byPrice = shop.findByPrice(Price(2000));
    std::cout << "Поиск по цене 20 руб. (2000 коп.): найдено " << byPrice.size() << " шт.\n";

    Product* foundById = shop.findById(1);
    if (foundById) {
        std::cout << "Поиск по ID 1: найден товар '" << foundById->getName() << "'\n";
    }

    std::cout << "\nУдаляем товар с ID 2 (Молоко)\n";
    bool removedById = shop.removeById(2);
    std::cout << "Результат удаления по ID: " << (removedById ? "Успешно" : "Не найден") << "\n";

    std::cout << "\nУдаляем товар по индексу\n";
    bool removedByIndex = shop.removeByIndex(0);
    std::cout << "Результат удаления по индексу: " << (removedByIndex ? "Успешно" : "Ошибка") << "\n";
    std::cout << "Размер склада после удалений: " << shop.size() << "\n";

    std::cout << "\n 5: Перемещение товара и изменение остатка\n";
    Warehouse newWarehouse(10);

    std::cout << "Перемещаем футболку (ID 3) на новый склад\n";
    bool moved = shop.transferProduct(3, newWarehouse);

    if (moved) {
        std::cout << "Успех! Футболка перемещена.\n";
        std::cout << "Товаров на старом складе осталось: " << shop.size() << "\n";

        Product* item = newWarehouse.findById(3);
        if (item) {
            std::cout << "Изменяем цену (на 25 руб.) и добавляем 5 шт. на новом складе\n";
            item->setPrice(Price(2500));
            item->changeQuantity(5);
            item->describe();
        }
    }
    else {
        std::cout << "Не удалось переместить (нет места или неверный ID).\n";
    }
    return 0;
}