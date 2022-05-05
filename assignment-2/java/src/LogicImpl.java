import javax.swing.*;

public class LogicImpl implements Logic {

    private final JLabel modalityLabel;
    private final JLabel productLabel;
    private final JLabel selfCheckLabel;

    LogicImpl(JLabel modalityLabel, JLabel productLabel, JLabel selfCheckLabel) {
        this.modalityLabel = modalityLabel;
        this.productLabel = productLabel;
        this.selfCheckLabel = selfCheckLabel;
    }

    @Override
    public void onRefill() {

    }

    @Override
    public void onRecover() {

    }
}
