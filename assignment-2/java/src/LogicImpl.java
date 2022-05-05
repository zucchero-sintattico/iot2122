import java.util.function.Consumer;

public class LogicImpl implements Logic {

    private final Consumer<String> modalityConsumer;
    private final Consumer<String> coffeeConsumer;
    private final Consumer<String> teaConsumer;
    private final Consumer<String> chocolateConsumer;
    private final Consumer<String> selfCheckConsumer;

    public LogicImpl(Consumer<String> modalityConsumer,
                     Consumer<String> coffeeConsumer,
                     Consumer<String> teaConsumer,
                     Consumer<String> chocolateConsumer,
                     Consumer<String> selfCheckConsumer) {
        this.modalityConsumer = modalityConsumer;
        this.coffeeConsumer = coffeeConsumer;
        this.teaConsumer = teaConsumer;
        this.chocolateConsumer = chocolateConsumer;
        this.selfCheckConsumer = selfCheckConsumer;
    }


    @Override
    public void onRefill() {
        // TODO: implement
    }

    @Override
    public void onRecover() {
        // TODO: implement
    }
}
