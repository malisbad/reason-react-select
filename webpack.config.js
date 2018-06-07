const path = require('path');
const outputDir = path.join(__dirname, "dist/");

module.exports = {
  entry: './src/Index.js',
  output: {
    path: outputDir,
    publicPath: outputDir,
    filename: 'Index.js',
  },
};
