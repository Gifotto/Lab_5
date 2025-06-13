import java.util.*;

public class QueueDistribution {

    // Структура посетителя очереди
    static class Visitor {
        String ticket;  // номер талона
        int duration;   // длительность посещения

        Visitor(String ticket, int duration) {
            this.ticket = ticket;
            this.duration = duration;
        }
    }

    // Структура окна для обработки посетителей
    static class Window implements Comparable<Window> {
        int id;                   // номер окна
        int totalTime = 0;        // суммарное время, которое уже занято
        List<String> tickets = new ArrayList<>(); // список талонов, обслуженных в этом окне

        Window(int id) {
            this.id = id;
        }

        // Приоритет в очереди по наименьшему totalTime
        @Override
        public int compareTo(Window other) {
            return Integer.compare(this.totalTime, other.totalTime);
        }
    }

    // Генератор уникальных номеров талонов
    static String generateTicket(Set<String> usedTickets) {
        Random random = new Random();
        String ticket;
        do {
            ticket = String.format("T%03d", random.nextInt(1000)); // формат T001, T034 и т.д.
        } while (usedTickets.contains(ticket)); // гарантируем уникальность

        usedTickets.add(ticket); // добавляем в множество использованных
        return ticket;
    }

    // Преобразование команды в числовой код для использования switch-case
    static int getCommandCode(String command) {
        return switch (command) {
            case "ENQUEUE" -> 1;
            case "DISTRIBUTE" -> 2;
            default -> 0; // неизвестная команда
        };
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        /*
        // Установка русской кодировки в Windows — не требуется в Java
        */

        System.out.println(">>> Введите кол-во окон");
        System.out.print("<<< ");
        int numWindows = scanner.nextInt();

        List<Visitor> visitors = new ArrayList<>();       // список всех посетителей
        Set<String> usedTickets = new HashSet<>();        // множество уже выданных талонов

        System.out.println("\nКоманды: ENQUEUE — команда принимает продолжительность посещения и выдает номер талона;");
        System.out.println("DISTRIBUTE — распределяет посетителей на окна\n");

        // Основной цикл ввода команд
        while (true) {
            System.out.print("<<< ");
            String command = scanner.next();

            switch (getCommandCode(command)) {
                case 1 -> { // ENQUEUE
                    int duration = scanner.nextInt();
                    String ticket = generateTicket(usedTickets); // создать уникальный талон
                    visitors.add(new Visitor(ticket, duration)); // добавить в очередь
                    System.out.println(">>> " + ticket);         // вывести номер талона
                }
                case 2 -> { // DISTRIBUTE
                    PriorityQueue<Window> windowQueue = new PriorityQueue<>();

                    // Инициализируем все окна
                    for (int i = 1; i <= numWindows; i++) {
                        windowQueue.add(new Window(i));
                    }

                    // Распределяем каждого посетителя в наименее загруженное окно
                    for (Visitor visitor : visitors) {
                        Window win = windowQueue.poll(); // получаем окно с минимальной загрузкой
                        assert win != null;
                        win.totalTime += visitor.duration; // увеличиваем общее время
                        win.tickets.add(visitor.ticket);   // добавляем талон в список
                        windowQueue.add(win);              // возвращаем окно обратно
                    }

                    // Собираем все окна из очереди в список
                    List<Window> result = new ArrayList<>(windowQueue);
                    result.sort(Comparator.comparingInt(w -> w.id)); // Сортируем по номеру окна

                    // Выводим результат распределения
                    for (Window win : result) {
                        System.out.print(">>> Окно " + win.id + " (" + win.totalTime + " минут): ");
                        for (int i = 0; i < win.tickets.size(); i++) {
                            System.out.print(win.tickets.get(i));
                            if (i + 1 < win.tickets.size()) System.out.print(", ");
                        }
                        System.out.println();
                    }

                    return; // Завершаем программу после распределения
                }
                default -> System.out.println(">>> Неизвестная команда");
            }
        }
    }
}
