package engel_lyndon;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Basic GUI form that will allow the user to input several features of their coffee mug to calculate the likelihood
 * of it mysteriously going miss. There are four input options: the base color, the number of prints on the mug, the
 * popularity of the mug, and whether it's damaged.
 *
 * @author Lyndon Engel
 */
public class MugProject
{
    private JComboBox colorSelect;
    private JButton run;
    private JTextField numPrints;
    private JSlider popSlider;
    private JCheckBox chipCheckbox;

    /**
     * This function builds the GUI interface. I start by creating and defining the JFrame. I then move onto creating
     * the layout. For the outside I choose to use a border layout and on the inside I used a gridlayout. After the
     * layouts were created I went on to add the JLabels and their corresponding components. I created an ActionListener
     * for the button. The listener runs the function onOK() which does all the calculations and error checking
     * for the probability of the cup getting stolen.
     */
    public MugProject()
    {
        //Creating and defining JFrame
        JFrame frame = new JFrame("Mug Safety");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setPreferredSize(new Dimension(400,300));

        //Setup borderlayout and create panel
        BorderLayout layout = new BorderLayout();
        JPanel panel = new JPanel(layout);

        //create inner gridlayout
        GridLayout gridLayout = new GridLayout(4,2);
        JPanel gridPanel = new JPanel(gridLayout);
        gridPanel.setBorder(new EmptyBorder(10,10,10,10));

        //Header label
        JLabel header = new JLabel("Is My Coffee Mug Safe?");
        header.setHorizontalAlignment(JLabel.CENTER);
        panel.add(header,BorderLayout.NORTH);

        //Color label
        JLabel colorLabel = new JLabel("Basic Color:    ");
        colorLabel.setHorizontalAlignment(JLabel.RIGHT);
        gridPanel.add(colorLabel);

        //drop down box for color select
        colorSelect = new JComboBox(new String[]{"White","Blue","Green","Shiny Silver", "Shiny Red"});
        colorSelect.setBorder(new EmptyBorder(15,15,15,15));
        gridPanel.add(colorSelect);

        //prints label
        JLabel printsLabel = new JLabel("Number of prints:  ");
        printsLabel.setHorizontalAlignment(JLabel.RIGHT);
        gridPanel.add(printsLabel);

        //print text field
        numPrints = new JTextField();
        numPrints.setBorder(new EmptyBorder(15,15,15,15));
        gridPanel.add(numPrints);

        //Popularity label
        JLabel popLabel = new JLabel("Popularity of Coffee Mug:");
        popLabel.setHorizontalAlignment(JLabel.RIGHT);
        gridPanel.add(popLabel);

        //Popularity Slider
        popSlider = new JSlider(0,10,1);
        popSlider.setBorder(new EmptyBorder(15,15,15,15));
        gridPanel.add(popSlider);

        //Chipped label
        JLabel chipLabel = new JLabel("Chipped? ");
        chipLabel.setHorizontalAlignment(JLabel.RIGHT);
        gridPanel.add(chipLabel);

        //Chipped Checkbox
        chipCheckbox = new JCheckBox("Check Me!",false);
        gridPanel.add(chipCheckbox);

        //Add gridlayout panel to the borderlayout panel in the center
        panel.add(gridPanel,BorderLayout.CENTER);

        //Bottom button
        run = new JButton("Likelihood of mysteriously disappearing");
        run.setHorizontalAlignment(JLabel.CENTER);
        panel.add(run,BorderLayout.SOUTH);

        //run onOk() on button click
        run.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                onOK();
            }
        });

        //Add the border panel to the frame and generate GUI
        frame.add(panel);
        frame.pack();
        frame.setVisible(true);
    }

    /**
     * Run the GUI
     *
     * @param args none
     */
    public static void main(String[] args)
    {
        MugProject mugp = new MugProject();
    }

    /**
     * Pretty basic function that calculates the probability for the cup getting stolen. Its starts by checking if the
     * number of prints entered is a correct number between 0-10. It then adds the percentage for the color of the cup,
     * popularity, and whether its chipped or not. After that is all added up it then outputs the corresponding message
     * box with the percentage chance it might be stolen.
     */
    private void onOK()
    {
        //number prints on cup
        int printNum;

        //probability the cup gets stolen, starting at a base of 1%
        double probability = 1;

        //try catch statment to see if the number of prints entered is a number and if its between 1 and 10
        try
        {
            //check if number
            printNum = Integer.parseInt(numPrints.getText());

            //number between 0 and 10
            if(printNum < 0 || printNum > 10)
            {
                throw new NumberFormatException();
            }

            //Printnum must be a number so multiply by 4 for number of prints
            probability += printNum * 4;
        }
        catch (NumberFormatException e)
        {
            //if print number is not valid output error message
            JOptionPane.showMessageDialog(null,"Invalid number of prints. It must be between 0 and 10!","Bad Number",JOptionPane.ERROR_MESSAGE);
            return;
        }

        //Grab color percentage using combobox index
        if(colorSelect.getSelectedIndex() >= 3 )
        {
            probability += 8;
        }
        else
        {
            if(colorSelect.getSelectedIndex() != 0)
            {
                probability += 5;
            }
        }

        //Add up popularity percentage
        probability += popSlider.getValue() * 5;

        //is there a chip
        if(chipCheckbox.isSelected())
        {
            probability = probability * .5;
        }

        //Output correct dialog box depending on probability
        if(probability >= 10)
        {
            JOptionPane.showMessageDialog(null,"Highly probable of going missing:\n"+ "Likelihood: " + probability + "%","That's no good",JOptionPane.WARNING_MESSAGE);
        }
        else
        {
            JOptionPane.showMessageDialog(null,"Coffee mug is likely safe.\n"+ "Likelihood: " + probability + "%","That's no good",JOptionPane.INFORMATION_MESSAGE);
        }
    }
}

