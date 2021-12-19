var inline = require('gulp-inline');
var gulp = require('gulp');

function inlineCssJs() {
  const folder = 'FB/';
  const srcName = 'index.html';
  const destName = 'solution';

  return gulp.src(folder + srcName)
    .pipe(inline({
      base: folder,
    }))
    .pipe(gulp.dest(folder + destName));
}

exports.inline = inlineCssJs;
exports.default = gulp.parallel(inlineCssJs);
