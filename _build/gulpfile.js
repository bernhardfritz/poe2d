var gulp = require('gulp');
var spawn = require('child_process').spawn;

gulp.task('default', ['run']);

gulp.task('run', function() {
    spawn('./sketch', [], { stdio: 'inherit' });
})

gulp.task('watch', function() {
    return gulp.watch(['../src/*.*', '../include/*.*'], ['make']);
});

gulp.task('make', function() {
    var isWin = process.platform === "win32";
    spawn(isWin ? 'mingw32-make' : 'make', [], { stdio: 'inherit' });
});