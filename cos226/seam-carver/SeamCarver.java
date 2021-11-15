import edu.princeton.cs.algs4.Picture;
import edu.princeton.cs.algs4.StdOut;

public class SeamCarver {

    double[][] energies;

    private double[] distTo;
    private int[][] edgeTo;

    private Picture picture;

    // create a seam carver object based on the given picture
    public SeamCarver(Picture picture) {
        if (picture == null) {
            throw new IllegalArgumentException();
        }
        this.picture = picture;
        this.energies = new double[picture.width()][picture.height()];
        for (int x = 0; x < picture.width(); x++) {
            for (int y = 0; y < picture.height(); y++) {
                energies[x][y] = energy(x, y);
            }
        }

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

    public double energy(int x, int y) {
        if (x > picture.height() || x < 0 || y > picture.width() || y < 0)
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

    // sequence of indices for horizontal seam

    public int[] findHorizontalSeam() {
        edgeTo = new int[width()][height()];
        distTo = new double[height()];
        int[] seam = new int[width()];
        double[] prevDistTo = new double[height()];

        double minWeight = Double.POSITIVE_INFINITY;
        int minIndex = 0;

        for (int i = 0; i < distTo.length; i++) {
            distTo[i] = Double.POSITIVE_INFINITY;
        }

        for (int x = 0; x < width(); x++) {
            for (int y = 0; y < height(); y++) {
                relaxHorizontal(x, y, prevDistTo, y - 1);
                relaxHorizontal(x, y, prevDistTo, y);
                relaxHorizontal(x, y, prevDistTo, y + 1);
            }
        }

        for (int i = 0; i < distTo.length; i++) {
            double weight = distTo[i];
            if (weight < minWeight) {
                minWeight = weight;
                minIndex = i;
            }
        }

        for (int x = width() - 1; x >= 0; x--) {
            seam[x] = minIndex;
            minIndex = edgeTo[minIndex][x];
        }

        return seam;


    }

    // sequence of indices for vertical seam
    public int[] findVerticalSeam() {
        edgeTo = new int[width()][height()];
        distTo = new double[width()];
        int[] seam = new int[height()];
        double[] prevDistTo = new double[width()];

        double minWeight = Double.POSITIVE_INFINITY;
        int minIndex = 0;

        for (int i = 0; i < distTo.length; i++) {
            distTo[i] = Double.POSITIVE_INFINITY;
        }

        for (int y = 0; y < height(); y++) {
            for (int x = 0; x < width(); x++) {
                relaxVertical(x, y, prevDistTo, x - 1);
                relaxVertical(x, y, prevDistTo, x);
                relaxVertical(x, y, prevDistTo, x + 1);

            }
        }

        for (int i = 0; i < distTo.length; i++) {
            double weight = distTo[i];
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

    private void relaxVertical(int x, int y, double[] prevDistTo, int prev) {
        if (prev < 0 || prev >= prevDistTo.length) {
            return;
        }

        double weight = prevDistTo[prev];
        double energy = energies[x][y];
        if (distTo[x] > weight + energy) {
            distTo[x] = weight + energy;
            edgeTo[x][y] = prev;
        }

    }

    private void relaxHorizontal(int x, int y, double[] prevDistTo, int prev) {
        if (prev < 0 || prev >= prevDistTo.length) {
            return;
        }

        double weight = prevDistTo[prev];
        double energy = energies[x][y];
        if (distTo[y] > weight + energy) {
            distTo[y] = weight + energy;
            edgeTo[x][y] = prev;
        }
    }


    // remove horizontal seam from current picture
    public void removeHorizontalSeam(int[] seam) {
        if (seam == null) {
            throw new IllegalArgumentException();
        }

    }

    // remove vertical seam from current picture
    public void removeVerticalSeam(int[] seam) {
        if (seam == null) {
            throw new IllegalArgumentException();
        }
    }

    private void remove(int[] seam, int width, int height) {
        Picture newPic = new Picture(width, height);

        for (int i = 0; i < width; i++) {
            
            for (int j = 0; j < height; j++) {

            }
        }

    }

    //  unit testing (required)
    public static void main(String[] args) {
        String filename = args[0];
        Picture picture = new Picture(filename);
        SeamCarver test = new SeamCarver(picture);

        StdOut.println("energy: " + test.energy(1, 2));

    }

}
