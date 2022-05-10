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
        String[] values = data.split(",");
        if (values.length < 6) {
            System.out.println("Missing values");
            return;
        }
        modalityConsumer.accept(values[0]);
        coffeeConsumer.accept(values[1]);
        teaConsumer.accept(values[2]);
        chocolateConsumer.accept(values[3]);
        selfCheckConsumer.accept(values[4]);
        System.out.println("Free memory: " + values[5]);
    }

}
