import java.util.function.Consumer;

public class LogicImpl implements Logic {

    // APP -> Arduino
    private static final String REFILL_MESSAGE = "REFILL";
    private static final String RECOVER_MESSAGE = "RECOVER";

    // Arduino -> APP
    private static final String MODALITY_MESSAGE = "MODALITY";
    private static final String INFO_MESSAGE = "INFO";
    private static final String SELFCHECK_MESSAGE = "SELFCHECK";

    SerialCommChannel channel;
    private final Consumer<String> modalityConsumer;
    private final Consumer<String> coffeeConsumer;
    private final Consumer<String> teaConsumer;
    private final Consumer<String> chocolateConsumer;
    private final Consumer<String> selfCheckConsumer;

    public LogicImpl(String COM,
                    Consumer<String> modalityConsumer,
                    Consumer<String> coffeeConsumer,
                    Consumer<String> teaConsumer,
                    Consumer<String> chocolateConsumer,
                    Consumer<String> selfCheckConsumer) throws Exception {
        this.modalityConsumer = modalityConsumer;
        this.coffeeConsumer = coffeeConsumer;
        this.teaConsumer = teaConsumer;
        this.chocolateConsumer = chocolateConsumer;
        this.selfCheckConsumer = selfCheckConsumer;
        this.channel = new SerialCommChannel(COM,9600);
        System.out.println("Waiting Arduino for rebooting...");
        Thread.sleep(4000);
        System.out.println("Ready.");


        new Thread( () -> {
            while (true) {
                try {
                    String msg = channel.receiveMsg();
                    acceptData(msg);
                    //Thread.sleep(50);
                } catch (Exception e) {
                    System.out.println(e);
                }
            }
        }).start();
    }


    @Override
    public void onRefill() {
        this.channel.sendMsg(LogicImpl.REFILL_MESSAGE);
    }

    @Override
    public void onRecover() {
        this.channel.sendMsg(LogicImpl.RECOVER_MESSAGE);
    }

    private void acceptData(String data) {
        if (!data.contains(":")) {
            System.out.println("Missing values on command");
            return;
        }
        String command = data.split(":")[0];
        String values = data.split(":")[1];
        switch (command) {
            case LogicImpl.MODALITY_MESSAGE -> modalityConsumer.accept(values);
            case LogicImpl.INFO_MESSAGE -> handleInfo(values);
            case LogicImpl.SELFCHECK_MESSAGE -> selfCheckConsumer.accept(values);
            default -> System.out.println("Incorrect command: " + command);
        }
    }

    private void handleInfo(String values) {
        String beverage[] = values.split(",");
        coffeeConsumer.accept(beverage[0]);
        teaConsumer.accept(beverage[1]);
        chocolateConsumer.accept(beverage[2]);
    }

}
