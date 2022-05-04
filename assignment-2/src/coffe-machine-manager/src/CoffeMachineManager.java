import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class CoffeMachineManager {

    static JLabel modalityLabel;
    static JLabel productLabel;
    static JLabel selfCheckLabel;

    public static void main(String[] args) throws Exception {

        JLabel modalityLabel = new JLabel("0");
        JLabel productLabel = new JLabel("0");
        JLabel selfCheckLabel = new JLabel("0");

        Logic logic = new LogicImpl(modalityLabel, productLabel, selfCheckLabel);

        //Creating the Frame
        JFrame frame = new JFrame("Coffer Machine Manager");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        // SOUTH Panel
        JPanel southPanel = new JPanel();
        JButton refill = new JButton("Refill");
        refill.addActionListener(e -> logic.onRefill());
        JButton recover = new JButton("Recover");
        recover.addActionListener(e -> logic.onRecover());

        southPanel.add(refill);
        southPanel.add(recover);

        // CENTER Panel
        JPanel centerPanel = new JPanel();
        centerPanel.setLayout(new BoxLayout(centerPanel, BoxLayout.PAGE_AXIS));

        JPanel modalityPanel = new JPanel();
        modalityPanel.add(new JLabel("Modality: "));
        modalityPanel.add(modalityLabel);

        JPanel productPanel = new JPanel();
        productPanel.add(new JLabel("Product: "));
        productPanel.add(productLabel);

        JPanel selfCheckPanel = new JPanel();
        selfCheckPanel.add(new JLabel("Self Check: "));
        selfCheckPanel.add(selfCheckLabel);

        centerPanel.add(modalityPanel);
        centerPanel.add(productPanel);
        centerPanel.add(selfCheckPanel);


        //Adding Components to the frame.
        frame.getContentPane().add(BorderLayout.SOUTH, southPanel);
        frame.getContentPane().add(BorderLayout.CENTER, centerPanel);
        frame.setVisible(true);
    }

}
