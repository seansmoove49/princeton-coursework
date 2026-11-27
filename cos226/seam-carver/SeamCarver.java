import edu.princeton.cs.algs4.Picture;
import edu.princeton.cs.algs4.StdOut;

public class SeamCarver {

    // picture object
    private Picture picture;

    // create a seam carver object based on the given picture
    public SeamCarver(Picture picture) {
        if (picture == null) {
            throw new IllegalArgumentException();
        }

        this.picture = new Picture(picture);
    }

    // current picture
    public Picture picture() {
        Picture copy = new Picture(picture);
        return copy;
    }

    // width of current picture
    public int width() {
        return picture.width();
    }

    // height of current picture
    public int height() {
        return picture.height();
    }

    // calculates energy of specified pixel
    public double energy(int x, int y) {
        if (x > width() - 1 || x < 0 || y > height() - 1 || y < 0)
            throw new IllegalArgumentException("Pixel outside of range");

        int height = picture.height();
        int width = picture.width();

        int xL = (x + width - 1) % width;
        int yT = (y + height - 1) % height;

        int xR = (x + width + 1) % width;
        int yB = (y + height + 1) % height;


        double energy = Math.sqrt(gradientEnergy(xL, y, xR, y)
                                          + gradientEnergy(x, yT, x, yB));

        return energy;
    }

    // calculate the square gradient between two pixels
    private double gradientEnergy(int x1, int y1, int x2, int y2) {
        int c1 = picture.getRGB(x1, y1);
        int c2 = picture.getRGB(x2, y2);

        int r1 = (c1 >> 16) & 0xFF;
        int g1 = (c1 >> 8) & 0xFF;
        int b1 = (c1 >> 0) & 0xFF;

        int r2 = (c2 >> 16) & 0xFF;
        int g2 = (c2 >> 8) & 0xFF;
        int b2 = (c2 >> 0) & 0xFF;

        double gradient = Math.pow((r2 - r1), 2) + Math.pow((g2 - g1), 2)
                + Math.pow((b2 - b1), 2);

        return gradient;
    }

    // transposes the picture
    private void transpose() {
        Picture transPic = new Picture(height(), width());
        for (int col = 0; col < width(); col++) {
            for (int row = 0; row < height(); row++) {
                transPic.setRGB(row, col, picture.getRGB(col, row));

            }
        }

        picture = transPic;
    }

    // sequence of indices for horizontal seam
    public int[] findHorizontalSeam() {
        transpose();
        int[] seam = findVerticalSeam();
        transpose();
        return seam;
    }

    // sequence of indices for vertical seam
    public int[] findVerticalSeam() {
        int[][] edgeTo = new int[width()][height()];
        double[][] distTo = new double[width()][height()];

        int[] seam = new int[height()]; // store x-value to remove for each row
        double[][] energies = new double[width()][height()];

        double minWeight = Double.POSITIVE_INFINITY;
        int minIndex = 0;

        for (int x = 0; x < picture.width(); x++) {
            for (int y = 0; y < picture.height(); y++) {
                energies[x][y] = energy(x, y);
            }
        }

        for (int i = 0; i < distTo.length; i++) {
            distTo[i][0] = energies[i][0];
        }
        for (int i = 0; i < distTo.length; i++) {
            for (int j = 1; j < distTo[0].length; j++) {
                distTo[i][j] = Double.POSITIVE_INFINITY;
            }

        }

        for (int y = 0; y < height(); y++) {
            for (int x = 0; x < width(); x++) {
                // straight down
                relax(x, y, x, y + 1, distTo, edgeTo, energies);

                // down, left
                relax(x, y, x - 1, y + 1, distTo, edgeTo, energies);

                // down, right
                relax(x, y, x + 1, y + 1, distTo, edgeTo, energies);

            }
        }

        for (int i = 0; i < distTo.length; i++) {
            double weight = distTo[i][height() - 1];
            if (weight < minWeight) {
                minWeight = weight;
                minIndex = i;
            }
        }

        for (int y = height() - 1; y >= 0; y--) {
            seam[y] = minIndex;
            minIndex = edgeTo[minIndex][y];
        }

        return seam;
    }

    // relaxes edges and updates smallest distTo and edgeTo arrays
    private void relax(int x, int y, int nextX, int nextY,
                       double[][] distTo, int[][] edgeTo, double[][] energies) {
        if (nextX < 0 || nextX >= distTo.length ||
                nextY < 0 || nextY >= distTo[0].length) return;

        double weight = distTo[x][y];
        double energy = energies[nextX][nextY];

        if (distTo[nextX][nextY] > weight + energy) {
            distTo[nextX][nextY] = weight + energy;
            edgeTo[nextX][nextY] = x;
        }
    }

    // validate the seam array
    private void validateSeam(int[] seam) {
        // length and null check
        if (seam == null)
            throw new IllegalArgumentException("Null argument");

        if (seam.length != height())
            throw new IllegalArgumentException("Argument of wrong length");

        if (width() == 1)
            throw new IllegalArgumentException("Width is equal to one");


        // check that seam does not have jumps
        for (int i = 0; i < seam.length - 1; i++) {
            if (Math.abs(seam[i + 1] - seam[i]) > 1)
                throw new IllegalArgumentException("Not a valid seam");
        }

        for (int i = 0; i < seam.length; i++) {
            if (seam[i] >= width() || seam[i] < 0)
                throw new IllegalArgumentException("Illegal Argument");
        }
    }

    // remove horizontal seam from current picture
    public void removeHorizontalSeam(int[] seam) {
        transpose();
        removeVerticalSeam(seam);
        transpose();
    }

    // remove vertical seam from current picture
    public void removeVerticalSeam(int[] seam) {
        validateSeam(seam);

        Picture newPic = new Picture(width() - 1, height());

        for (int row = 0; row < height(); row++) {
            for (int col = 0; col < newPic.width(); col++) {
                if (col < seam[row])
                    newPic.setRGB(col, row, picture.getRGB(col, row));
                else
                    newPic.setRGB(col, row, picture.getRGB(col + 1, row));
            }
        }

        picture = newPic;
    }


    //  unit testing (required)
    public static void main(String[] args) {
        Picture pic = new Picture("3x4.png");
        SeamCarver sc = new SeamCarver(pic);

        StdOut.println("(0, 0) " + sc.energy(0, 0));
        StdOut.println(sc.height());
        StdOut.println(sc.width());
        StdOut.println(sc.picture());

        int[] vertSeam = sc.findVerticalSeam();
        int[] horSeam = sc.findHorizontalSeam();
        sc.removeVerticalSeam(vertSeam);
        sc.removeHorizontalSeam(horSeam);
        StdOut.println((sc.height()));
        StdOut.println((sc.width()));


    }

}
