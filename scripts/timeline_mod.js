
/**
 * JS test file
 */

(function ($) {

  $(document).ready(function() {
    $('.access a').on('click', function(event){
      event.preventDefault();
      $('html, body').animate({
        scrollTop: $('.timelinejs_table').offset().top
        }, 'fast');
    });
  });

  $(window).load(function(){

    $('#storyjs-timeline').on('LOADED', function(event){
      window.location = '#2';
      window.location = '#1';
    });

    $('#storyjs-timeline').on('UPDATE', function(event){

      var target = event.target;
      if($(target).hasClass('vco-slider')){

        $('.slider-item-container').children('div.slider-item').each(function(){
            var date = $(this).find($('h2.date')).html();
            var headline = '<span class="capitalize">' + $(this).find($('h3')).html() + '</span>';
            if(!!date && !!headline){
              var newHeadline = '<div class="headline">'+ headline + ' - ' + date  +'</div>';
              var check = $(this).find($('div.headline'));
              if(!!check){
                $(this).find($('.headline')).remove();
                $(this).prepend(newHeadline);
              }
            }
          });

      }
    });
  });

})(jQuery);

