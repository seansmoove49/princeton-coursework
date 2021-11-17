Programming Assignment 7: Seam Carving


/* *****************************************************************************
 *  Describe concisely your algorithm to find a horizontal (or vertical)
 *  seam.
 **************************************************************************** */
Our algorithm iterates through the picture in topological order and relaxes
the edges. We did so by keeping track of a distTo array which stored the
sum of that specific pixel's energy and the smallest sum of energies to
reach one of its parents. We also kept track of an edgeTo array which
keeps track of which parent of that specific pixel contribute to the energy.
After relaxing, we find the minimum sum energy from the bottom and iterate up
to get the seam array.


/* *****************************************************************************
 *  Describe what makes an image suitable to the seam-carving approach
 *  (in terms of preserving the content and structure of the original
 *  image, without introducing visual artifacts). Describe an image that
 *  would not work well.
 **************************************************************************** */
An image that has stretches of similar sections would be suitable for seam
carving.


/* *****************************************************************************
 *  Perform computational experiments to estimate the running time to reduce
 *  a W-by-H image by one column and one row (i.e., one call each to
 *  findVerticalSeam(), removeVerticalSeam(), findHorizontalSeam(), and
 *  removeHorizontalSeam()). Use a "doubling" hypothesis, where you
 *  successively increase either W or H by a constant multiplicative
 *  factor (not necessarily 2).
 *
 *  To do so, fill in the two tables below. Each table must have 5-10
 *  data points, ranging in time from around 0.25 seconds for the smallest
 *  data point to around 30 seconds for the largest one.
 **************************************************************************** */

(keep W constant)
 W = 2000
 multiplicative factor (for H) = 2.75

 H           time (seconds)      ratio       log ratio
------------------------------------------------------
200             0.235
550             0.448           1.90        0.634
1513            0.935           2.08        0.724
4159            2.493           2.67        0.971
11438           7.923           3.18        1.144
31455           23.58           2.98        1.079


(keep H constant)
 H = 2000
 multiplicative factor (for W) = 2.75

 W           time (seconds)      ratio       log ratio
------------------------------------------------------
250             0.314
688             0.535           1.704          0.525
1891            1.398           2.613          0.949
5199            3.432           2.455          0.889
14298           10.205          2.973          1.077
39319           33.432          3.276          1.173




/* *****************************************************************************
 *  Using the empirical data from the above two tables, give a formula
 *  (using tilde notation) for the running time (in seconds) as a function
 *  of both W and H, such as
 *
 *       ~ 5.3*10^-8 * W^5.1 * H^1.5
 *
 *  Briefly explain how you determined the formula for the running time.
 *  Recall that with tilde notation, you include both the coefficient
 *  and exponents of the leading term (but not lower-order terms).
 *  Round each coefficient and exponent to two significant digits.
 **************************************************************************** */
We get the exponents from our log ratios and then we can solve for the
coefficients by plugging in values and solving. In our case, we plug in
T(2000, 31455) = 23.58 and then solving for a we get 3.509 * 10^-8

Running time (in seconds) to find and remove one horizontal seam and one
vertical seam, as a function of both W and H:


    ~  3.509 * 10^-8 * W^1.08 * H^1.17
       _______________________________________




/* *****************************************************************************
 *  Known bugs / limitations.
 **************************************************************************** */
N/A

/* *****************************************************************************
 *  Describe whatever help (if any) that you received.
 *  Don't include readings, lectures, and precepts, but do
 *  include any help from people (including course staff, lab TAs,
 *  classmates, and friends) and attribute them by name.
 **************************************************************************** */
Course staff: Laura Leal

/* *****************************************************************************
 *  Describe any serious problems you encountered.
 **************************************************************************** */
N/A

/* *****************************************************************************
 *  If you worked with a partner, assert below that you followed
 *  the protocol as described on the assignment page. Give one
 *  sentence explaining what each of you contributed.
 **************************************************************************** */
We both worked on SeamCarver together.

/* *****************************************************************************
 *  List any other comments here. Feel free to provide any feedback
 *  on how much you learned from doing the assignment, and whether
 *  you enjoyed doing it.
 **************************************************************************** */
N/A
