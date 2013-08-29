
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

    $(document).on('keydown', '.storyjs-embed', function(e){
      aa();
    });
    $(document).on('click', '.flag', aa);

    $(document).on('UPDATE', '#storyjs-timeline', function(event) {
      var target = event.target;
      if($(target).hasClass('vco-slider')){
        aa();
      }
    });

    $(document).on('LOADED', '#storyjs-timeline', function(event){
      var target = event.target;
      if($(target).hasClass('vco-navigation')){
        var newHeadline = '<div class="headline"><span class="capitalize">Basin Plan comes into effect</span> - November 2012 </div>';
        $('.slider-item-container div.slider-item:nth-child(2)').prepend(newHeadline);
        $('.content .marker:nth-child(2) .flag').trigger('click');
      }

    });
  });

  function aa(){
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

})(jQuery);

