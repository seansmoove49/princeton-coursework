// Party_even_cut_even_choose.java: sample implementation for Party
// COS 445 SD2, Spring 2019
// Created by Andrew Wonnacott

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Party_sw42 implements Party {
    final boolean _isBeta;

    private Party_sw42(boolean isBeta) {
        _isBeta = isBeta;
    }

    // must construct and return a Party based on the provided blocks. Do any
    // initialization here.
    public static Party New(boolean isBeta, int numDistricts, List<Block> blocks) {
        return new Party_sw42(isBeta);
    }

    // Make the most even districts easily possible (e.g. greedily put the districts
    // with the biggest
    // difference together)
    public List<List<Block>> cut(int r, List<Block> remaining) {
        List<List<Block>> ret = new ArrayList<List<Block>>();

        if (remaining.size() == 3) {
            long num_a = 0;
            long num_b = 0;

            for (Block block : remaining) {
                num_a += block.alpha();
                num_b += block.beta();
            }

            long total = num_a + num_b;


            // if it is beta
            if (_isBeta) {
                if (num_b / total > 1 / 2) {
                    // // districtSize
                    remaining = new ArrayList<Block>(remaining); // get mutability
                    Collections.sort(remaining, new Block.BlockComparator(true, true, true));
                    // now sorted in decreasing order of partisanship
                    final int districtSize = remaining.size() / r;
                    long[] betaSwings = new long[r];
                    for (int i = 0; i < r; ++i) {
                    List<Block> district = new ArrayList<Block>();
                    ret.add(district);
                    }
                    // this is inefficient, but idrc
                    for (Block block : remaining) {
                    int extremum = -1;
                    for (int i = 0; i < r; ++i) {
                        List<Block> district = ret.get(i);
                        if (district.size() == districtSize)
                        continue;
                        if (extremum == -1)
                        extremum = i;
                        // we swing beta and this is the most alpha blockyet
                        if (block.betaSwing() > 0 && betaSwings[i] < betaSwings[extremum])
                        extremum = i;
                        // we swing alpha and this is the most beta block yet
                        if (block.betaSwing() < 0 && betaSwings[i] > betaSwings[extremum])
                        extremum = i;
                        // if we hit zero swing blocks then it doesn't matter anyhow;
                    }
                    ret.get(extremum).add(block);
                    // pulls down the swing on the beta swing
                    betaSwings[extremum] += block.betaSwing();
                    }
                    return ret;

                }

                // }
                else {
                    remaining = new ArrayList<Block>(remaining); // get mutability
                    Collections.sort(remaining, new Block.BlockComparator(false, true, !_isBeta));
                    // now sorted in increasing order of how many more votes the other party gets
                    final int districtSize = remaining.size() / r;
                    for (int i = 0; i < r; ++i) {
                    List<Block> district = new ArrayList<Block>();
                    for (int j = 0; j < districtSize; ++j) {
                        district.add(remaining.get(i * districtSize + j));
                    }
                    ret.add(district);
                    }
                    return ret;

                }
            }

            else {
                if (num_a / total > 1 / 2) {
                    // // districtSize
                    remaining = new ArrayList<Block>(remaining); // get mutability
                    Collections.sort(remaining, new Block.BlockComparator(true, true, true));
                    // now sorted in decreasing order of partisanship
                    final int districtSize = remaining.size() / r;
                    long[] betaSwings = new long[r];
                    for (int i = 0; i < r; ++i) {
                    List<Block> district = new ArrayList<Block>();
                    ret.add(district);
                    }
                    // this is inefficient, but idrc
                    for (Block block : remaining) {
                    int extremum = -1;
                    for (int i = 0; i < r; ++i) {
                        List<Block> district = ret.get(i);
                        if (district.size() == districtSize)
                        continue;
                        if (extremum == -1)
                        extremum = i;
                        // we swing beta and this is the most alpha blockyet
                        if (block.betaSwing() > 0 && betaSwings[i] < betaSwings[extremum])
                        extremum = i;
                        // we swing alpha and this is the most beta block yet
                        if (block.betaSwing() < 0 && betaSwings[i] > betaSwings[extremum])
                        extremum = i;
                        // if we hit zero swing blocks then it doesn't matter anyhow;
                    }
                    ret.get(extremum).add(block);
                    // pulls down the swing on the beta swing
                    betaSwings[extremum] += block.betaSwing();
                    }
                    return ret;

                }
                // if (num_a / total > 1 / 3) {

                // }
                else {
                    remaining = new ArrayList<Block>(remaining); // get mutability
                    Collections.sort(remaining, new Block.BlockComparator(false, true, !_isBeta));
                    // now sorted in increasing order of how many more votes the other party gets
                    final int districtSize = remaining.size() / r;
                    for (int i = 0; i < r; ++i) {
                    List<Block> district = new ArrayList<Block>();
                    for (int j = 0; j < districtSize; ++j) {
                        district.add(remaining.get(i * districtSize + j));
                    }
                    ret.add(district);
                    }
                    return ret;

                }

            }
        }

        int sum_betaSwing = 0; // b-a
        for (int i = 0; i < remaining.size(); i++) {
            sum_betaSwing += remaining.get(i).betaSwing();
        }

        // if we have more votes than the opponent, cut
        // the districts such that there is an even distribution of votes in each
        // district.
        if ((sum_betaSwing < 0 && !_isBeta) || (sum_betaSwing > 0 && _isBeta)) {
            remaining = new ArrayList<Block>(remaining); // get mutability
            Collections.sort(remaining, new Block.BlockComparator(true, true, true));
            // now sorted in decreasing order of partisanship
            final int districtSize = remaining.size() / r;
            long[] betaSwings = new long[r];
            for (int i = 0; i < r; ++i) {
                List<Block> district = new ArrayList<Block>();
                ret.add(district);
            }
            // this is inefficient, but idrc
            for (Block block : remaining) {
                int extremum = -1;
                for (int i = 0; i < r; ++i) {
                    List<Block> district = ret.get(i);
                    if (district.size() == districtSize)
                        continue;
                    if (extremum == -1)
                        extremum = i;
                    // we swing beta and this is the most alpha blockyet
                    if (block.betaSwing() > 0 && betaSwings[i] < betaSwings[extremum])
                        extremum = i;
                    // we swing alpha and this is the most beta block yet
                    if (block.betaSwing() < 0 && betaSwings[i] > betaSwings[extremum])
                        extremum = i;
                    // if we hit zero swing blocks then it doesn't matter anyhow;
                }
                ret.get(extremum).add(block);
                // pulls down the swing on the beta swing
                betaSwings[extremum] += block.betaSwing();
            }
        }

        // less voters than opponent then we cut unevenly
        else {
            remaining = new ArrayList<Block>(remaining); // get mutability
            Collections.sort(remaining, new Block.BlockComparator(false, true, !_isBeta));
            // now sorted in increasing order of how many more votes the other party gets
            final int districtSize = remaining.size() / r;
            for (int i = 0; i < r; ++i) {
                List<Block> district = new ArrayList<Block>();
                for (int j = 0; j < districtSize; ++j) {
                    district.add(remaining.get(i * districtSize + j));
                }
                ret.add(district);
            }
        }

        return ret;

    }

    // Return the district we win which we win by the closest margin (or, if none,
    // the one we lose by
    // the largest)
    public List<Block> choose(List<List<Block>> districts) {

        // closestWinMarign
        long closestWinMargin = -1;
        List<Block> closestWinDistrict = null;

        // Furthest Lost Margin
        long furthestLossMargin = -1;
        List<Block> furthestLossDistrict = null;

        // for each district in district
        for (List<Block> district : districts) {
            long ourFavor = 0;
            for (Block block : district) {

                // beta swing = how many more voters beta has than alpha in the block
                // basically the favor count is calculated
                ourFavor += _isBeta ? block.betaSwing() : -block.betaSwing();
            }

            // n.b. tiebreaks in favor of beta
            if (ourFavor > 0 || (ourFavor == 0 && _isBeta)) {

                // inital one and if we have a smaller favort than closestWinMargin we set it
                if (closestWinDistrict == null || closestWinMargin > ourFavor) {
                    closestWinMargin = ourFavor;
                    closestWinDistrict = district;
                }
            } else {
                // ourFavor is negative, so store the min
                if (furthestLossDistrict == null || furthestLossMargin > ourFavor) {
                    furthestLossMargin = ourFavor;
                    furthestLossDistrict = district;
                }
            }
        }

        if (districts.size() == 3) {
            long num_a = 0;
            long num_b = 0;
            for (List<Block> district : districts) {
                for (Block block : district) {
                    num_a += block.alpha();
                    num_b += block.beta();
                }
            }

            long total = num_a + num_b;
            long alpha = 0;
            long beta = 0; 

            if (closestWinDistrict != null) {
                for (Block block : closestWinDistrict) {
                    beta += block.beta();
                    alpha += block.alpha();
                }
            }
            
            long to_remove = _isBeta ? beta : alpha;


            long remaining = 0;
            if (_isBeta) {
                if ((num_b - to_remove) / (total - to_remove) < 1 / 4) {
                    

                    for (Block block : furthestLossDistrict) {
                        remaining += block.beta();
                    }

                }
                if ((num_b - remaining) / (total - remaining) > 1 / 2) {

                    return furthestLossDistrict;

                }


            } else {
                if ((num_a - to_remove) / (total - to_remove) < 1 / 4) {

                    for (Block block : furthestLossDistrict) {
                        remaining += block.alpha();
                    }
                
                }
                if ((num_a - remaining) / (total - remaining) > 1 / 2) {

                    return furthestLossDistrict;

                }
            }
        }
        return (closestWinDistrict != null) ? closestWinDistrict : furthestLossDistrict;

    }

    // inform the active party of the choice made by the nonactive party
    public void accept(List<Block> chosen) {
    }
}
