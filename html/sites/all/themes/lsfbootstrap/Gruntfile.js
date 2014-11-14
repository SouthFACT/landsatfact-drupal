module.exports = function(grunt) {

    // Project configuration.
    grunt.initConfig({
	    pkg: grunt.file.readJSON('package.json'),
	    less: {
		development: {
		    options: {
			paths: ["less", "bootstrap"]
		    },
		    files: {
			"css/style.css": "less/style.less"
		    }
		},
		production: {
		    options: {
			paths: ["less", "bootstrap"],
			cleancss: true
		    },
		    files: {
			"css/style.css": "less/style.less"
		    }
		}
	    }
	});

    // Load the plugin that provides the "uglify" task.
    grunt.loadNpmTasks('grunt-contrib-less');

    // Default task(s).
    grunt.registerTask('default', ['less:development']);

};