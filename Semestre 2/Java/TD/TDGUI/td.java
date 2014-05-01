import java.awt.*;
import javax.swing.*;
public class Exo extends JFrame{

    public static void apparitionFenetre(){new Exo();}

    public Exo(){

        this.setTitle("Creation - suppression de boutons");

        JPanel monpanel = new JPanel();
        monpanel.addActionListener(new MonActionListener());
        monpanel.setLayout(new BorderLayout());
        JButton boutonCrea = new JButton("Creation");
        JButton boutonSup = new JButton("Suppression");
        monpanel.add(boutonCrea, BorderLayout, NORTH);
        monpanel.add(boutonSup, BorderLayout, SOUTH);
        boutonCrea.addActionListener(new MonActionListener());
        boutonSup.addActionListener(new MonActionListener());
        this.getContentPanel().add(monpanel);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);
    }

    public class MonActionListener implements ActionListener{

        public void actionPerformed(ActionEvent a){

            if(getSource() = boutonCrea){
            }
            else {
        }
    }

    public static void main(String args[]){

        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                apparitionFenetre();
            }
        });
    }
}
