import edu.princeton.cs.algs4.Picture;
import edu.princeton.cs.algs4.StdOut;

import java.awt.Color;

public class SeamCarver {

    double[][] energies;

    private Picture picture;

    // create a seam carver object based on the given picture
    public SeamCarver(Picture picture) {
        this.picture = picture;
        this.energies = new double[height()][width()];
    }

    // current picture
    public Picture picture() {
        return picture;
    }

    // width of current picture
    public int width() {
        return picture.width();
    }

    // height of current picture
    public int height() {
        return picture.height();
    }

    // energy of pixel at column x and row y
    public double energy(int x, int y) {

        if (x < 0 || x > width() - 1 || y < 0 || y > width() - 1)
            throw new IllegalArgumentException();
        Color colorLeft = picture.get(width() - 1, y);
        Color colorRight = picture.get(0, y);
        Color colorTop = picture.get(x, height() - 1);
        Color colorBottom = picture.get(x, 0);

        if (x != 0) {
            colorLeft = picture.get(x - 1, y);
        }
        if (x != width() - 1) {
            colorRight = picture.get(x + 1, y);
        }
        if (y != 0) {
            colorTop = picture.get(x, y - 1);
        }
        if (y != height() - 1) {
            colorBottom = picture.get(x, y + 1);
        }
        double xGradientSquared = (colorRight.getRed() - colorLeft.getRed()) *
                (colorRight.getRed() - colorLeft.getRed())
                + (colorRight.getBlue() - colorLeft.getBlue()) *
                (colorRight.getBlue() - colorLeft.getBlue())
                + (colorRight.getGreen() - colorLeft.getGreen()) *
                (colorRight.getGreen() - colorLeft.getGreen());
        double yGradientSquared = (colorTop.getRed() - colorBottom.getRed()) *
                (colorTop.getRed() - colorBottom.getRed())
                + (colorTop.getBlue() - colorBottom.getBlue()) *
                (colorTop.getBlue() - colorBottom.getBlue())
                + (colorTop.getGreen() - colorBottom.getGreen()) *
                (colorTop.getGreen() - colorBottom.getGreen());
        double energy = Math.sqrt(xGradientSquared + yGradientSquared);
        return energy;

    }

    // sequence of indices for horizontal seam
    // public int[] findHorizontalSeam() {
    //
    // }

    // sequence of indices for vertical seam
    // public int[] findVerticalSeam() {
    //
    // }

    // remove horizontal seam from current picture
    public void removeHorizontalSeam(int[] seam) {

    }

    // remove vertical seam from current picture
    public void removeVerticalSeam(int[] seam) {

    }

    //  unit testing (required)
    public static void main(String[] args) {
        String filename = args[0];
        Picture picture = new Picture(filename);
        SeamCarver test = new SeamCarver(picture);

        StdOut.println("energy: " + test.energy(1, 2));

    }

}
