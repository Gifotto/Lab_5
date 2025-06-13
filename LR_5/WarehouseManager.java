import java.util.*;

public class WarehouseManager {
    // Константы склада
    private static final int maxPerCell = 10;
    private static final int numZones = 2;
    private static final int numShelves = 4;
    private static final int numSections = 18;
    private static final int numLevels = 5;
    private static final int totalCapacity = numZones * numShelves * numSections * numLevels * maxPerCell;

    // Типы данных
    private static final Map<String, Map<String, Integer>> warehouse = new HashMap<>();

    // Проверка правильности адреса ячейки
    private static boolean isValidCell(String addr) {
        if (addr.length() < 5 || !(addr.charAt(0) == 'A' || addr.charAt(0) == 'Б')) return false;
        try {
            int shelf = Character.getNumericValue(addr.charAt(1));
            int section = Integer.parseInt(addr.substring(2, 4));
            int level = Character.getNumericValue(addr.charAt(4));

            return shelf >= 1 && shelf <= numShelves &&
                   section >= 1 && section <= numSections &&
                   level >= 1 && level <= numLevels;
        } catch (NumberFormatException | IndexOutOfBoundsException e) {
            return false;
        }
    }

    // Подсчёт загруженности ячейки
    private static int cellLoad(String cell) {
        int sum = 0;
        Map<String, Integer> products = warehouse.getOrDefault(cell, Collections.emptyMap());
        for (int qty : products.values()) {
            sum += qty;
        }
        return sum;
    }

    // Добавление товара
    private static void addProduct(String name, int qty, String cell) {
        if (!isValidCell(cell)) {
            System.out.println("Неверный адрес ячейки.");
            return;
        }

        int current = cellLoad(cell);
        if (current + qty > maxPerCell) {
            System.out.println("Ошибка: Ячейка переполнена. Доступно: " + (maxPerCell - current));
            return;
        }

        warehouse.computeIfAbsent(cell, k -> new HashMap<>());
        warehouse.get(cell).put(name, warehouse.get(cell).getOrDefault(name, 0) + qty);
        System.out.println("Товар добавлен.");
    }

    // Удаление товара
    private static void remProduct(String name, int qty, String cell) {
        if (!isValidCell(cell) || !warehouse.containsKey(cell) || !warehouse.get(cell).containsKey(name)) {
            System.out.println("Ошибка: Товар не найден в ячейке.");
            return;
        }

        int currentQty = warehouse.get(cell).get(name);
        if (currentQty < qty) {
            System.out.println("Ошибка: Недостаточно товара. В наличии: " + currentQty);
            return;
        }

        warehouse.get(cell).put(name, currentQty - qty);
        if (warehouse.get(cell).get(name) == 0) {
            warehouse.get(cell).remove(name);
            if (warehouse.get(cell).isEmpty()) {
                warehouse.remove(cell);
            }
        }

        System.out.println("Товар удален.");
    }

    // Информация о складе
    private static void info() {
        int totalUsed = 0;
        Map<Character, Integer> zoneUsed = new HashMap<>();

        for (Map.Entry<String, Map<String, Integer>> entry : warehouse.entrySet()) {
            String cell = entry.getKey();
            Map<String, Integer> products = entry.getValue();
            int cellQty = 0;

            for (int qty : products.values()) {
                cellQty += qty;
            }

            totalUsed += cellQty;
            char zone = cell.charAt(0);
            zoneUsed.put(zone, zoneUsed.getOrDefault(zone, 0) + cellQty);
        }

        System.out.printf("Загрузка склада: %.2f%%\n", totalUsed * 100.0 / totalCapacity);

        for (char zone : new char[] {'А', 'Б'}) {
            int zoneCapacity = numShelves * numSections * numLevels * maxPerCell;
            double zoneLoad = zoneUsed.getOrDefault(zone, 0) * 100.0 / zoneCapacity;
            System.out.printf("Зона %c: %.2f%%\n", zone, zoneLoad);
        }

        System.out.println("\nСодержимое ячеек:");
        for (Map.Entry<String, Map<String, Integer>> entry : warehouse.entrySet()) {
            System.out.println(entry.getKey() + ":");
            for (Map.Entry<String, Integer> productEntry : entry.getValue().entrySet()) {
                System.out.println("  " + productEntry.getKey() + ": " + productEntry.getValue());
            }
        }

        System.out.println("\nПустые ячейки:");
        for (char zone : new char[] {'А', 'Б'}) {
            for (int shelf = 1; shelf <= numShelves; ++shelf) {
                for (int section = 1; section <= numSections; ++section) {
                    for (int level = 1; level <= numLevels; ++level) {
                        String addr = zone +
                                Integer.toString(shelf) +
                                String.format("%02d", section) +
                                Integer.toString(level);
                        if (!warehouse.containsKey(addr)) {
                            System.out.print(addr + " ");
                        }
                    }
                }
            }
        }
        System.out.println();
    }

    // Главный метод
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Склад: команды\n ADD <наименование товара> <количество> <адрес ячейки**>\n REMOVE <наименование товара> <количество> <адрес ячейки>\n INFO\n EXIT\n");
        System.out.println("**Адрес ячейки:\n1) А, Б - зона хранения - теплый, холодный склад;\n"
                + "2) 0 - порядковый номер стеллажа;\n"
                + "3) 00 - порядковый номер вертикальной секции стеллажа;\n"
                + "4) 0 - порядковый номер полки.\n");

        while (true) {
            System.out.print("> ");
            String command = scanner.next().toUpperCase();

            if (command.equals("ADD")) {
                String name = scanner.next();
                int qty = scanner.nextInt();
                String cell = scanner.next();
                addProduct(name, qty, cell);

            } else if (command.equals("REMOVE")) {
                String name = scanner.next();
                int qty = scanner.nextInt();
                String cell = scanner.next();
                remProduct(name, qty, cell);

            } else if (command.equals("INFO")) {
                info();

            } else if (command.equals("EXIT")) {
                break;

            } else {
                System.out.println("Неизвестная команда.");
            }
        }

        scanner.close();
    }
}
