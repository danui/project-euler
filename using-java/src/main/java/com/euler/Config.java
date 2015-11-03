package com.euler;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Config {

    private static interface ProblemLoader {
        public Problem load();
    }

    private static final Map<String,ProblemLoader> LOADERS = new HashMap<>();
    {
        LOADERS.put("24", new ProblemLoader() {
            @Override
            public Problem load() {
                return new Problem24();
            }
        });
    }

    private static Problem loadProblem(String key) {
        ProblemLoader loader = LOADERS.get(key);
        if (loader == null) {
            // TODO Print a list of known problems then.
            throw new IllegalArgumentException(
                "Not a known problem: "+key);
        }
        return loader.load();
    }

    private final String[] args;

    public Config(String[] args) {
        this.args = args;
    }

    public List<Problem> getProblems() {
        List<Problem> result = new ArrayList<>();
        for (int i = 0; i < args.length; ++i) {
            result.add(loadProblem(args[i]));
        }
        return result;
    }

}
