import java.util.function.Consumer;

public class LogicImpl implements Logic {

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
    }


    @Override
    public void onRefill() {
        // TODO: implement
        try {
            String msg = this.channel.receiveMsg();
            System.out.println("Received: "+msg);
        } catch (Exception e) {
            System.out.println(e);
        }

    }

    @Override
    public void onRecover() {
        // TODO: implement
    }
}
