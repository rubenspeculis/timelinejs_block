
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
        // This is being used for the purpose of pre-propulating the first
        // instance of the timeline 
        var newHeadline = '<div class="headline"><span class="capitalize">Basin Plan comes into effect</span> - November 2012 </div>';
        $('#timeline_1 .slider-item-container div.slider-item:nth-child(2)').prepend(newHeadline);
        $('#timeline_1 .content .marker:nth-child(2) .flag').trigger('click');
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

  function kk(event){
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

  $.eventReport = function(selector, root) {
    var s = [];
    $(selector || '*', root).andSelf().each(function() {

        var e = $.data(this, 'events');
        if(!e) return;
        s.push(this.tagName);
        if(this.id) s.push('#', this.id);
        if(this.className) s.push('.', this.className.replace(/ +/g, '.'));
        for(var p in e) {
          var r = e[p],
          h = r.length - r.delegateCount;
          if(h)
            s.push('\n', h, ' ', p, ' handler', h > 1 ? 's' : '');
          if(r.delegateCount) {
            for(var q = 0; q < r.length; q++)
              if(r[q].selector) s.push('\n', p, ' for ', r[q].selector);
          }
        }
        s.push('\n\n');
      });
    return s.join('');
  }

  $.fn.eventReport = function(selector) {
    return $.eventReport(selector, this);
  }

})(jQuery);

